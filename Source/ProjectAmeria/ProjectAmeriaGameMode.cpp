// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectAmeriaGameMode.h"
#include "ProjectAmeriaCharacter.h"
#include "NPC/NPCCharacter.h"
#include "EngineUtils.h"
#include "MyPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"


AProjectAmeriaGameMode::AProjectAmeriaGameMode()
{
	// set default pawn class to our Blueprinted character
    bIsTurnBasedMode = true;

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_Player"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
        PlayerControllerClass = AMyPlayerController::StaticClass();
	}

    static ConstructorHelpers::FClassFinder<UUserWidget> ActionWidgetClassFinder(TEXT("/Game/UI/WBP_ActionPointsWidget"));
    if (ActionWidgetClassFinder.Succeeded())
    {
        ActionPointsWidgetClass = ActionWidgetClassFinder.Class;
    }

    static ConstructorHelpers::FClassFinder<UUserWidget> WidgetClassFinder(TEXT("/Game/UI/WBP_TurnInfoWidget"));
    if (WidgetClassFinder.Succeeded())
    {
        TurnInfoWidgetClass = WidgetClassFinder.Class;
    }

    InitialWidgetPosition = FVector2D(50, 50);
    WidgetOffset = FVector2D(0, 30);

    PrimaryActorTick.bCanEverTick = true; // Tickを有効にする
}

void AProjectAmeriaGameMode::BeginPlay()
{
    Super::BeginPlay();

    if (TurnInfoWidgetClass)
    {
        TurnInfoWidget = CreateWidget<UUserWidget>(GetWorld(), TurnInfoWidgetClass);
        if (TurnInfoWidget)
        {
            TurnInfoWidget->AddToViewport();
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("TurnInfoWidgetClass is NULL"));
    }
    StartTurn();

}

void AProjectAmeriaGameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (bIsTurnBasedMode)
    {
        UpdateActionPointsUI(); // 毎フレーム行動力UIを更新
    }
}

void AProjectAmeriaGameMode::StartTurn()
{
    // ターンが始まるたびにすべてのキャラクターの行動力をリセット
    if (!bIsTurnBasedMode) return;

    if (AProjectAmeriaCharacter* PlayerCharacter = Cast<AProjectAmeriaCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
    {
        PlayerCharacter->SetCurrentActionPoints(PlayerCharacter->GetMaxActionPoints());
    }

    for (TActorIterator<ANPCCharacter> It(GetWorld()); It; ++It)
    {
        It->SetCurrentActionPoints(It->GetMaxActionPoints());
    }
    CurrentTurnState = PlayerTurn;
    HandlePlayerTurn();
    UpdateTurnInfoUI();
    UpdateActionPointsUI();
    bCanEndTurn = false;
}

void AProjectAmeriaGameMode::NextTurn()
{
    if (!bIsTurnBasedMode) return;

    switch (CurrentTurnState)
    {
    case PlayerTurn:
        CurrentTurnState = AllyNPCTurn;
        HandleAllyNPCTurn();
        break;
    case AllyNPCTurn:
        CurrentTurnState = EnemyNPCTurn;
        HandleEnemyNPCTurn();
        break;
    case EnemyNPCTurn:
        CurrentTurnState = PlayerTurn;
      //  HandlePlayerTurn();
        StartTurn();
        break;
    }
    UpdateTurnInfoUI();
}

void AProjectAmeriaGameMode::ToggleGameMode()
{
    bIsTurnBasedMode = !bIsTurnBasedMode;
    UE_LOG(LogTemp, Log, TEXT("Game Mode Toggled: %s"), bIsTurnBasedMode ? TEXT("Turn-Based") : TEXT("Free Movement"));

    UpdateTurnInfoUI();  // モード切り替え時にUIを更新

    if (bIsTurnBasedMode)
    {
        StartTurn();
    }
}

void AProjectAmeriaGameMode::HandlePlayerTurn()
{
    // プレイヤーのターンロジック
    bCanEndTurn = true;
}

void AProjectAmeriaGameMode::HandleAllyNPCTurn()
{
    // 味方NPCのターンロジック
    for (TActorIterator<ANPCCharacter> It(GetWorld()); It; ++It)
    {
        if (It->Affiliation == EAffiliation::Ally)
        {
            It->PerformAction();
        }
    }
    bCanEndTurn = true;
}
void AProjectAmeriaGameMode::HandleEnemyNPCTurn()
{
    // 敵NPCのターンロジック
     // すべての敵NPCの行動を実行
    for (TActorIterator<ANPCCharacter> It(GetWorld()); It; ++It)
    {
        if (It->Affiliation == EAffiliation::Enemy)
        {
            It->PerformAction();
        }
    }
    bCanEndTurn = true;
}

void AProjectAmeriaGameMode::EndTurn()
{
    if (bCanEndTurn)
    {
        bCanEndTurn = false; // フラグをリセット
        NextTurn();
    }
}

void AProjectAmeriaGameMode::UpdateTurnInfoUI()
{
    if (TurnInfoWidget)
    {
        UTextBlock* TurnText = Cast<UTextBlock>(TurnInfoWidget->GetWidgetFromName("TurnText"));
        if (TurnText)
        {
            FString TurnInfo;
            if (bIsTurnBasedMode)
            {
                switch (CurrentTurnState)
                {
                case PlayerTurn:
                    TurnInfo = "Turn: Player";
                    break;
                case AllyNPCTurn:
                    TurnInfo = "Turn: Ally NPC";
                    break;
                case EnemyNPCTurn:
                    TurnInfo = "Turn: Enemy NPC";
                    break;
                }
            }
            else
            {
                TurnInfo = "Not Turn Mode";
            }
            TurnText->SetText(FText::FromString(TurnInfo));
        }
    }
}

void AProjectAmeriaGameMode::UpdateActionPointsUI()
{
    FVector2D CurrentPosition = InitialWidgetPosition;

    // プレイヤーキャラクターの行動力を表示
    if (AProjectAmeriaCharacter* PlayerCharacter = Cast<AProjectAmeriaCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
    {
        UUserWidget** PlayerActionPointsWidgetPtr = ActionPointsWidgets.Find(PlayerCharacter);
        UUserWidget* PlayerActionPointsWidget = PlayerActionPointsWidgetPtr ? *PlayerActionPointsWidgetPtr : nullptr;
        if (!PlayerActionPointsWidget && ActionPointsWidgetClass)
        {
            PlayerActionPointsWidget = CreateWidget<UUserWidget>(GetWorld(), ActionPointsWidgetClass);
            if (PlayerActionPointsWidget)
            {
                PlayerActionPointsWidget->AddToViewport();
                ActionPointsWidgets.Add(PlayerCharacter, PlayerActionPointsWidget);
            }
        }
        if (PlayerActionPointsWidget)
        {
            UTextBlock* ActionPointsText = Cast<UTextBlock>(PlayerActionPointsWidget->GetWidgetFromName("ActionPointsText"));
            if (ActionPointsText)
            {
                UpdateTextBlockPosition(ActionPointsText, CurrentPosition);
                FString ActionPointsString = FString::Printf(TEXT("Player AP: %d"), static_cast<int32>(PlayerCharacter->GetCurrentActionPoints()));
                ActionPointsText->SetText(FText::FromString(ActionPointsString));
            }
           // UE_LOG(LogTemp, Log, TEXT("Player Action Points Widget position set to: X=%f, Y=%f"), CurrentPosition.X, CurrentPosition.Y);
        }
        CurrentPosition += WidgetOffset;
    }

    // NPCキャラクターの行動力を表示
    for (TActorIterator<ANPCCharacter> It(GetWorld()); It; ++It)
    {
        ANPCCharacter* NPC = *It;
        UUserWidget** ActionPointsWidgetPtr = ActionPointsWidgets.Find(NPC);
        UUserWidget* ActionPointsWidget = ActionPointsWidgetPtr ? *ActionPointsWidgetPtr : nullptr;
        if (!ActionPointsWidget && ActionPointsWidgetClass)
        {
            ActionPointsWidget = CreateWidget<UUserWidget>(GetWorld(), ActionPointsWidgetClass);
            if (ActionPointsWidget)
            {
                ActionPointsWidget->AddToViewport();
                ActionPointsWidgets.Add(NPC, ActionPointsWidget);
            }
        }
        if (ActionPointsWidget)
        {
            UTextBlock* ActionPointsText = Cast<UTextBlock>(ActionPointsWidget->GetWidgetFromName("ActionPointsText"));
            if (ActionPointsText)
            {
                UpdateTextBlockPosition(ActionPointsText, CurrentPosition);
                FString ActionPointsString;
                switch (NPC->Affiliation)
                {
                case EAffiliation::Ally:
                    ActionPointsString = FString::Printf(TEXT("Ally AP: %d"), static_cast<int32>(NPC->GetCurrentActionPoints()));
                    break;
                case EAffiliation::Enemy:
                    ActionPointsString = FString::Printf(TEXT("Enemy AP: %d"), static_cast<int32>(NPC->GetCurrentActionPoints()));
                    break;
                default:
                    ActionPointsString = FString::Printf(TEXT("NPC AP: %d"), static_cast<int32>(NPC->GetCurrentActionPoints()));
                    break;
                }
                ActionPointsText->SetText(FText::FromString(ActionPointsString));
            }
         //   UE_LOG(LogTemp, Log, TEXT("NPC Action Points Widget position set to: X=%f, Y=%f"), CurrentPosition.X, CurrentPosition.Y);
        }
        CurrentPosition += WidgetOffset;
    }
}

void AProjectAmeriaGameMode::UpdateTextBlockPosition(UTextBlock* TextBlock, FVector2D Position)
{
    if (TextBlock)
    {
        UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(TextBlock->Slot);
        if (CanvasSlot)
        {
            CanvasSlot->SetPosition(Position);
        //    UE_LOG(LogTemp, Log, TEXT("TextBlock position set to: X=%f, Y=%f"), Position.X, Position.Y);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("TextBlock is not in a Canvas Panel Slot"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("TextBlock is null"));
    }
}

