// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectAmeriaCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "ProjectAmeriaGameMode.h"
#include <Kismet/GameplayStatics.h>
#include "UObject/ConstructorHelpers.h"
#include "UObject/UObjectGlobals.h"
#include "Action/ActionUtility.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AProjectAmeriaCharacter

AProjectAmeriaCharacter::AProjectAmeriaCharacter()
{
	// �Փ˃J�v�Z���̃T�C�Y�ݒ�
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// �R���g���[���[����]���Ă��L�����N�^�[�͉�]���Ȃ�
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// �L�����N�^�[�̈ړ��ݒ�
	GetCharacterMovement()->bOrientRotationToMovement = true; // ���͕����ɃL�����N�^�[���ړ�
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ���̉�]���x�ňړ�

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// �J�����u�[�����쐬�i�L�����N�^�[�̌��ɃJ������z�u�j
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // ���̋����ŃL�����N�^�[�̌��ɃJ������z�u
	CameraBoom->bUsePawnControlRotation = true; // �R���g���[���[�Ɋ�Â��ăA�[������]

	// �t�H���[�J�������쐬
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; // �J�����̓A�[���ɑ΂��ĉ�]���Ȃ�

	// �s���͂̏����l�ݒ�
	MaxActionPoints = 10.0f;
	CurrentActionPoints = MaxActionPoints;

	// �X�e�[�^�X���`
	PlayerStats = CreateDefaultSubobject<UUnitStats>(TEXT("PlayerStats"));

	// �X�e�[�g�}�V���̏�����
	CurrentState = EPlayerState::Idle;

	// �^�[�Q�b�g�I���֘A�̏�����
	CurrentTarget = nullptr;
	bIsSelectingTarget = false;
}

void AProjectAmeriaCharacter::SetAffiliation(EAffiliation NewAffiliation)
{
	//�v���C���[�L������ALLY�Œ�
	return;
}

EAffiliation AProjectAmeriaCharacter::GetAffiliation() const
{
	return EAffiliation::Ally;
}

void AProjectAmeriaCharacter::BeginPlay()
{
	// �e�N���X��BeginPlay���Ăяo��
	Super::BeginPlay();
}

void AProjectAmeriaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	switch (CurrentState)
	{
	case EPlayerState::Idle:
		HandleIdleState();
		break;
	case EPlayerState::SelectingTarget:
		HandleSelectingTargetState();
		break;
	case EPlayerState::Attacking:
		HandleAttackingState();
		break;
	default:
		break;
	}
}


//////////////////////////////////////////////////////////////////////////
// Input

void AProjectAmeriaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// ���̓}�b�s���O�R���e�L�X�g��ǉ�
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// �A�N�V�����o�C���f�B���O��ݒ�
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// �W�����v
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// �ړ�
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AProjectAmeriaCharacter::Move);

		// ���_����
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AProjectAmeriaCharacter::Look);

		// ���̃^�[��
		EnhancedInputComponent->BindAction(NextTurnAction, ETriggerEvent::Started, this, &AProjectAmeriaCharacter::NextTurn);

		// �Q�[�����[�h�ؑ�
		EnhancedInputComponent->BindAction(ToggleModeAction, ETriggerEvent::Started, this, &AProjectAmeriaCharacter::ToggleGameMode);

		// �^�[�Q�b�g�I���A�N�V����
		EnhancedInputComponent->BindAction(SelectTargetAction, ETriggerEvent::Started, this, &AProjectAmeriaCharacter::SelectTarget);

		// �U���A�N�V����
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AProjectAmeriaCharacter::Attack);


	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AProjectAmeriaCharacter::Move(const FInputActionValue& Value)
{
	// ���͂�Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr && (IsTurnBasedMode() ? CanAct() : true) && (MovementVector.X != 0.0f || MovementVector.Y != 0.0f))
	{
		// �O���̕������擾
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// �O���x�N�g�����擾
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// �E�����x�N�g�����擾
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// �ړ���ǉ�
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);


		// �ړ����Ƃ�1�|�C���g����
		if (IsTurnBasedMode())
		{
			DecreaseActionPoints(1.0f);
		}
	}
}

void AProjectAmeriaCharacter::Look(const FInputActionValue& Value)
{
	// ���͂�Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// �R���g���[���[�ɑ΂���Yaw��Pitch��ǉ�
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AProjectAmeriaCharacter::DecreaseActionPoints(float Amount)
{
	CurrentActionPoints = FMath::Max(0.0f, CurrentActionPoints - Amount);
	//UE_LOG(LogTemplateCharacter, Log, TEXT("Action points remain: %f"), CurrentActionPoints);
	
	// �s���͂��[���ɂȂ����玟�̃^�[���ֈڍs����
	if (CurrentActionPoints <= 0.0f)
	{
		if (AProjectAmeriaGameMode* GameMode = Cast<AProjectAmeriaGameMode>(UGameplayStatics::GetGameMode(this)))
		{
			GameMode->HandlePlayerTurn();
		}
	}
}

void AProjectAmeriaCharacter::ExecuteAction(UActionBase* Action)
{
	if (Action && CurrentActionPoints >= Action->GetActionPointCost())
	{
		Action->ExecuteAction(this);
	}
}

bool AProjectAmeriaCharacter::CanAct() const
{
	return CurrentActionPoints > 0.0f;
}

float AProjectAmeriaCharacter::GetCurrentActionPoints() const
{
	return CurrentActionPoints;
}

void AProjectAmeriaCharacter::SetCurrentActionPoints(float Points)
{
	CurrentActionPoints = Points;
}

float AProjectAmeriaCharacter::GetMaxActionPoints() const
{
	return MaxActionPoints;
}

void AProjectAmeriaCharacter::SetMaxActionPoints(float Points)
{
	MaxActionPoints = Points;
}

void AProjectAmeriaCharacter::NextTurn()
{
	if (AProjectAmeriaGameMode* GameMode = Cast<AProjectAmeriaGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->EndTurn();
	}
}

void AProjectAmeriaCharacter::ToggleGameMode()
{
	if (AProjectAmeriaGameMode* GameMode = Cast<AProjectAmeriaGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->ToggleGameMode();
	}
}

void AProjectAmeriaCharacter::AddAction(TSubclassOf<UActionBase> ActionClass)
{
	if (*ActionClass)
	{
		ActionSlots.Add(ActionClass);
	}
}

void AProjectAmeriaCharacter::RemoveAction(TSubclassOf<UActionBase> ActionClass)
{
	if (*ActionClass)
	{
		ActionSlots.Remove(ActionClass);
	}
}

void AProjectAmeriaCharacter::Attack(const FInputActionValue& Value)
{
	int32 ActionIndex = 0; // ��: �A�N�V�����X���b�g�̍ŏ��̃A�N�V�������g�p����
	if (ActionSlots.IsValidIndex(ActionIndex))
	{
		UActionBase* Action = NewObject<UActionBase>(this, ActionSlots[ActionIndex]);
		if (Action)
		{
			ExecuteAction(Action);
		}
	}
}
bool AProjectAmeriaCharacter::IsTurnBasedMode() const
{
	if (const AProjectAmeriaGameMode* GameMode = Cast<AProjectAmeriaGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		return GameMode->IsTurnBasedMode();
	}
	return false;
}


float AProjectAmeriaCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (ActualDamage > 0.0f)
	{
		float NewHealth = FMath::Max(0.0f, PlayerStats->GetHealth() - ActualDamage);
		PlayerStats->SetHealth(NewHealth);

		UE_LOG(LogTemp, Log, TEXT("%s : HP = %f"), *GetName(), PlayerStats->GetHealth());

		// �L�����N�^�[���_���[�W���󂯂����̒ǉ����W�b�N
		if (NewHealth <= 0)
		{
			// �L�����N�^�[�̎��S����
			UE_LOG(LogTemp, Log, TEXT("%s has died"), *GetName());
		}
	}

	return ActualDamage;
}

//�X�e�[�g�}�V���@�A�C�h�����
void AProjectAmeriaCharacter::HandleIdleState()
{
	// �ҋ@��Ԃ̏���
}

//�X�e�[�g�}�V���U���ΏۑI�����
void AProjectAmeriaCharacter::HandleSelectingTargetState()
{
	// �^�[�Q�b�g�I����Ԃ̏���
}

//�X�e�[�g�}�V���U���I�����
void AProjectAmeriaCharacter::HandleAttackingState()
{
	// �U����Ԃ̏���
}

void AProjectAmeriaCharacter::ChangeState(EPlayerState NewState)
{
	CurrentState = NewState;
}

void AProjectAmeriaCharacter::SelectTarget()
{
	if (CurrentState == EPlayerState::Idle)
	{
		ChangeState(EPlayerState::SelectingTarget);

		TArray<AActor*> PotentialTargets;
		UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UActionCharaInterface::StaticClass(), PotentialTargets);


		// �����ōł��߂��^�[�Q�b�g��I��
		AActor* NearestTarget = nullptr;
		float NearestDistance = FLT_MAX;
		FVector PlayerLocation = GetActorLocation();

		for (AActor* Target : PotentialTargets)
		{
			// �������g�����O
			if (Target == this)
			{
				continue;
			}

			float Distance = FVector::Dist(PlayerLocation, Target->GetActorLocation());
			if (Distance < NearestDistance)
			{
				NearestDistance = Distance;
				NearestTarget = Target;
			}
		}

		CurrentTarget = NearestTarget;

		if (CurrentTarget)
		{
			UE_LOG(LogTemp, Log, TEXT("Target selected: %s"), *CurrentTarget->GetName());
			// �����Ƀn�C���C�g�\����C���W�P�[�^��ǉ�
		}
	}
	else if (CurrentState == EPlayerState::SelectingTarget)
	{
		ExecuteAttack();
		ChangeState(EPlayerState::Idle);
	}
}

void AProjectAmeriaCharacter::ExecuteAttack()
{
	if (CurrentTarget)
	{
		int32 ActionIndex = 0; // ��: �A�N�V�����X���b�g�̍ŏ��̃A�N�V�������g�p����
		UActionBase* Action=UActionUtility::CreateNewAction(GetWorld(), ActionSlots[ActionIndex]);
		Action->ExecuteAction(this, CurrentTarget);
		CurrentTarget = nullptr; // �^�[�Q�b�g�����Z�b�g
	}
}