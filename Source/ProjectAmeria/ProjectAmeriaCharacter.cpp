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
	// 衝突カプセルのサイズ設定
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// コントローラーが回転してもキャラクターは回転しない
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// キャラクターの移動設定
	GetCharacterMovement()->bOrientRotationToMovement = true; // 入力方向にキャラクターが移動
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // この回転速度で移動

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// カメラブームを作成（キャラクターの後ろにカメラを配置）
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // この距離でキャラクターの後ろにカメラを配置
	CameraBoom->bUsePawnControlRotation = true; // コントローラーに基づいてアームを回転

	// フォローカメラを作成
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false; // カメラはアームに対して回転しない

	// 行動力の初期値設定
	MaxActionPoints = 10.0f;
	CurrentActionPoints = MaxActionPoints;

	// ステータスを定義
	PlayerStats = CreateDefaultSubobject<UUnitStats>(TEXT("PlayerStats"));

	// ステートマシンの初期化
	CurrentState = EPlayerState::Idle;

	// ターゲット選択関連の初期化
	CurrentTarget = nullptr;
	bIsSelectingTarget = false;
}

void AProjectAmeriaCharacter::SetAffiliation(EAffiliation NewAffiliation)
{
	//プレイヤーキャラはALLY固定
	return;
}

EAffiliation AProjectAmeriaCharacter::GetAffiliation() const
{
	return EAffiliation::Ally;
}

void AProjectAmeriaCharacter::BeginPlay()
{
	// 親クラスのBeginPlayを呼び出す
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
	// 入力マッピングコンテキストを追加
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// アクションバインディングを設定
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// ジャンプ
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// 移動
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AProjectAmeriaCharacter::Move);

		// 視点操作
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AProjectAmeriaCharacter::Look);

		// 次のターン
		EnhancedInputComponent->BindAction(NextTurnAction, ETriggerEvent::Started, this, &AProjectAmeriaCharacter::NextTurn);

		// ゲームモード切替
		EnhancedInputComponent->BindAction(ToggleModeAction, ETriggerEvent::Started, this, &AProjectAmeriaCharacter::ToggleGameMode);

		// ターゲット選択アクション
		EnhancedInputComponent->BindAction(SelectTargetAction, ETriggerEvent::Started, this, &AProjectAmeriaCharacter::SelectTarget);

		// 攻撃アクション
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &AProjectAmeriaCharacter::Attack);


	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AProjectAmeriaCharacter::Move(const FInputActionValue& Value)
{
	// 入力はVector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr && (IsTurnBasedMode() ? CanAct() : true) && (MovementVector.X != 0.0f || MovementVector.Y != 0.0f))
	{
		// 前方の方向を取得
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// 前方ベクトルを取得
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// 右方向ベクトルを取得
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// 移動を追加
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
	// 入力はVector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// コントローラーに対してYawとPitchを追加
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

		// キャラクターがダメージを受けた時の追加ロジック
		if (NewHealth <= 0)
		{
			// キャラクターの死亡処理
			UE_LOG(LogTemp, Log, TEXT("%s has died"), *GetName());
		}
	}

	return ActualDamage;
}

//ステートマシン　アイドル状態
void AProjectAmeriaCharacter::HandleIdleState()
{
	// 待機状態の処理
}

//ステートマシン攻撃対象選択状態
void AProjectAmeriaCharacter::HandleSelectingTargetState()
{
	// ターゲット選択状態の処理
}

//ステートマシン攻撃選択状態
void AProjectAmeriaCharacter::HandleAttackingState()
{
	// 攻撃状態の処理
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


		// 距離で最も近いターゲットを選択
		AActor* NearestTarget = nullptr;
		float NearestDistance = FLT_MAX;
		FVector PlayerLocation = GetActorLocation();

		for (AActor* Target : PotentialTargets)
		{
			// 自分自身を除外
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
			// ここにハイライト表示やインジケータを追加
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
		int32 ActionIndex = 0; // 例: アクションスロットの最初のアクションを使用する
		UActionBase* Action=UActionUtility::CreateNewAction(GetWorld(), ActionSlots[ActionIndex]);
		Action->ExecuteAction(this, CurrentTarget);
		CurrentTarget = nullptr; // ターゲットをリセット
	}
}