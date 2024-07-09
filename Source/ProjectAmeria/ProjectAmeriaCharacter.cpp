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

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AProjectAmeriaCharacter

AProjectAmeriaCharacter::AProjectAmeriaCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// 行動力の初期値設定
	MaxActionPoints = 10.0f;
	CurrentActionPoints = MaxActionPoints;

	PlayerStats = CreateDefaultSubobject<UUnitStats>(TEXT("PlayerStats"));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void AProjectAmeriaCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

//////////////////////////////////////////////////////////////////////////
// Input

void AProjectAmeriaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AProjectAmeriaCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AProjectAmeriaCharacter::Look);

		// Next Turn
		EnhancedInputComponent->BindAction(NextTurnAction, ETriggerEvent::Started, this, &AProjectAmeriaCharacter::NextTurn);
		// Toggle Game Mode
		EnhancedInputComponent->BindAction(ToggleModeAction, ETriggerEvent::Started, this, &AProjectAmeriaCharacter::ToggleGameMode);

		// Attack Action
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AProjectAmeriaCharacter::Attack);

	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AProjectAmeriaCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr && (IsTurnBasedMode() ? CanAct() : true) && (MovementVector.X != 0.0f || MovementVector.Y != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);


		// 移動ごとに1ポイント消費
		if (IsTurnBasedMode())
		{
			DecreaseActionPoints(1.0f);
		}
	}
}

void AProjectAmeriaCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AProjectAmeriaCharacter::DecreaseActionPoints(float Amount)
{
	CurrentActionPoints = FMath::Max(0.0f, CurrentActionPoints - Amount);
	//UE_LOG(LogTemplateCharacter, Log, TEXT("Action points remain: %f"), CurrentActionPoints);
	// 行動力がゼロになったら次のターンへ移行する
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
	int32 ActionIndex = 0; // 例: アクションスロットの最初のアクションを使用する
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

		// Additional logic for when the character takes damage
		if (NewHealth <= 0)
		{
			// Handle character death
			UE_LOG(LogTemp, Log, TEXT("%s has died"), *GetName());
		}
	}

	return ActualDamage;
}

float AProjectAmeriaCharacter::GetStrength() const
{
	return PlayerStats->GetStrength();
}

void AProjectAmeriaCharacter::SetStrength(float Value)
{
	PlayerStats->SetStrength(Value);
}

float AProjectAmeriaCharacter::GetMagicPower() const
{
	return PlayerStats->GetMagicPower();
}

void AProjectAmeriaCharacter::SetMagicPower(float Value)
{
	PlayerStats->SetMagicPower(Value);
}

float AProjectAmeriaCharacter::GetDefense() const
{
	return PlayerStats->GetEndurance();
}

void AProjectAmeriaCharacter::SetDefense(float Value)
{
	PlayerStats->SetEndurance(Value);
}

float AProjectAmeriaCharacter::GetResistance() const
{
	return PlayerStats->GetMagicResistance();
}

void AProjectAmeriaCharacter::SetResistance(float Value)
{
	PlayerStats->SetMagicResistance(Value);
}

float AProjectAmeriaCharacter::GetHealth() const
{
	return PlayerStats->GetHealth();
}

void AProjectAmeriaCharacter::SetHealth(float Value)
{
	PlayerStats->SetHealth(Value);
}

float AProjectAmeriaCharacter::GetMana() const
{
	return PlayerStats->GetMana();
}

void AProjectAmeriaCharacter::SetMana(float Value)
{
	PlayerStats->SetMana(Value);
}

float AProjectAmeriaCharacter::GetEndurance() const
{
	return PlayerStats->GetEndurance();
}

void AProjectAmeriaCharacter::SetEndurance(float Value)
{
	PlayerStats->SetEndurance(Value);
}

float AProjectAmeriaCharacter::GetAgility() const
{
	return PlayerStats->GetAgility();
}

void AProjectAmeriaCharacter::SetAgility(float Value)
{
	PlayerStats->SetAgility(Value);
}

float AProjectAmeriaCharacter::GetDexterity() const
{
	return PlayerStats->GetDexterity();
}

void AProjectAmeriaCharacter::SetDexterity(float Value)
{
	PlayerStats->SetDexterity(Value);
}

float AProjectAmeriaCharacter::GetIntelligence() const
{
	return PlayerStats->GetIntelligence();
}

void AProjectAmeriaCharacter::SetIntelligence(float Value)
{
	PlayerStats->SetIntelligence(Value);
}

float AProjectAmeriaCharacter::GetCharisma() const
{
	return PlayerStats->GetCharisma();
}

void AProjectAmeriaCharacter::SetCharisma(float Value)
{
	PlayerStats->SetCharisma(Value);
}