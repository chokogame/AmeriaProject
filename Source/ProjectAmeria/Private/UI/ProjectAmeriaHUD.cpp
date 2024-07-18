// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ProjectAmeriaHUD.h"
#include "UI/UIUtility.h"
#include "NPC/NPCCharacter.h"
#include "EngineUtils.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanelSlot.h"
#include "../ProjectAmeriaGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AProjectAmeriaHUD::AProjectAmeriaHUD()
{
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

    static ConstructorHelpers::FClassFinder<UUserWidget> DebugWidgetClassFinder(TEXT("/Game/UI/WBP_DebugWindow"));
    if (DebugWidgetClassFinder.Succeeded())
    {
        DebugWindowClass = DebugWidgetClassFinder.Class;
    }
}

void AProjectAmeriaHUD::BeginPlay()
{
    Super::BeginPlay();

    // ターン情報ウィジェットの初期化と表示
    if (TurnInfoWidgetClass)
    {
        TurnInfoWidget = CreateWidget<UUserWidget>(GetWorld(), TurnInfoWidgetClass);
        if (TurnInfoWidget)
        {
            TurnInfoWidget->AddToViewport();
            // 初期ターン情報を設定
            UpdateTurnInfoUI(true, ETurnState::PlayerTurn);  // プレイヤーターンを初期設定
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to create TurnInfoWidget"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("TurnInfoWidgetClass is NULL"));
    }
    // プレイヤーのアクションポイントウィジェットの初期化と表示
    if (ActionPointsWidgetClass)
    {
        if (AProjectAmeriaCharacter* PlayerCharacter = Cast<AProjectAmeriaCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
        {
            UUserWidget* PlayerActionPointsWidget = CreateWidget<UUserWidget>(GetWorld(), ActionPointsWidgetClass);
            if (PlayerActionPointsWidget)
            {
                PlayerActionPointsWidget->AddToViewport();
                ActionPointsWidgets.Add(PlayerCharacter, PlayerActionPointsWidget);
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Failed to create PlayerActionPointsWidget"));
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("ActionPointsWidgetClass is NULL"));
    }
    // NPCのアクションポイントウィジェットの初期化と表示
    for (TActorIterator<ANPCCharacter> It(GetWorld()); It; ++It)
    {
        ANPCCharacter* NPC = *It;
        if (ActionPointsWidgetClass)
        {
            UUserWidget* ActionPointsWidget = CreateWidget<UUserWidget>(GetWorld(), ActionPointsWidgetClass);
            if (ActionPointsWidget)
            {
                ActionPointsWidget->AddToViewport();
                ActionPointsWidgets.Add(NPC, ActionPointsWidget);
            }
            else
            {
                UE_LOG(LogTemp, Warning, TEXT("Failed to create ActionPointsWidget for NPC"));
            }
        }
    }

    //デバッグ表示
    bIsDebugWindowVisible = false;

    if (DebugWindowClass)
    {
        DebugWindow = CreateWidget<UUserWidget>(GetWorld(), DebugWindowClass);
        if (DebugWindow)
        {
            DebugWindow->AddToViewport();
            DebugWindow->SetVisibility(ESlateVisibility::Hidden);
            DebugText = Cast<UTextBlock>(DebugWindow->GetWidgetFromName(TEXT("DebugText")));
        }
    }
    CurrentCharacterIndex = 0;
    CurrentDebugText = TEXT("");
 
}


void AProjectAmeriaHUD::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    // テキストが変更された場合のみ更新
    if (DebugText && DebugText->GetText().ToString() != CurrentDebugText)
    {
        DebugText->SetText(FText::FromString(CurrentDebugText));
    }
}

void AProjectAmeriaHUD::UpdateTurnInfoUI(bool bIsTurnBasedMode, ETurnState CurrentTurnState)
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
                case ETurnState::PlayerTurn : // PlayerTurn
                    TurnInfo = "Turn: Player";
                    break;
                case  ETurnState::AllyNPCTurn : // AllyNPCTurn
                    TurnInfo = "Turn: Ally NPC";
                    break;
                case ETurnState::EnemyNPCTurn: // EnemyNPCTurn
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

void AProjectAmeriaHUD::UpdateActionPointsUI()
{
    FVector2D CurrentPosition = InitialWidgetPosition;

    // プレイヤーのアクションポイントウィジェットの更新
    if (AProjectAmeriaCharacter* PlayerCharacter = Cast<AProjectAmeriaCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
    {
        UUserWidget** PlayerActionPointsWidgetPtr = ActionPointsWidgets.Find(PlayerCharacter);
        UUserWidget* PlayerActionPointsWidget = PlayerActionPointsWidgetPtr ? *PlayerActionPointsWidgetPtr : nullptr;
        if (PlayerActionPointsWidget)
        {
            UTextBlock* ActionPointsText = Cast<UTextBlock>(PlayerActionPointsWidget->GetWidgetFromName("ActionPointsText"));
            if (ActionPointsText)
            {
                UpdateTextBlockPosition(ActionPointsText, CurrentPosition);
                FString ActionPointsString = FString::Printf(TEXT("Player AP: %d"), static_cast<int32>(PlayerCharacter->GetCurrentActionPoints()));
                ActionPointsText->SetText(FText::FromString(ActionPointsString));
                UE_LOG(LogTemp, Log, TEXT("Player Action Points: %s"), *ActionPointsString);
            }
        }
        CurrentPosition += WidgetOffset;
    }

    // NPCのアクションポイントウィジェットの更新
    for (TActorIterator<ANPCCharacter> It(GetWorld()); It; ++It)
    {
        ANPCCharacter* NPC = *It;
        UUserWidget** ActionPointsWidgetPtr = ActionPointsWidgets.Find(NPC);
        UUserWidget* ActionPointsWidget = ActionPointsWidgetPtr ? *ActionPointsWidgetPtr : nullptr;
        if (ActionPointsWidget)
        {
            UTextBlock* ActionPointsText = Cast<UTextBlock>(ActionPointsWidget->GetWidgetFromName("ActionPointsText"));
            if (ActionPointsText)
            {
                UpdateTextBlockPosition(ActionPointsText, CurrentPosition);
                FString ActionPointsString = FString::Printf(TEXT("NPC AP: %d"), static_cast<int32>(NPC->GetCurrentActionPoints()));
                ActionPointsText->SetText(FText::FromString(ActionPointsString));
                UE_LOG(LogTemp, Log, TEXT("%s Action Points: %s"), *NPC->GetName(), *ActionPointsString);
            }
        }
        CurrentPosition += WidgetOffset;
    }
}

void AProjectAmeriaHUD::UpdateTextBlockPosition(UTextBlock* TextBlock, FVector2D Position)
{
    if (TextBlock)
    {
        UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(TextBlock->Slot);
        if (CanvasSlot)
        {
            CanvasSlot->SetPosition(Position);
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


void AProjectAmeriaHUD::ToggleDebugWindow()
{
    if (DebugWindow)
    {
        bIsDebugWindowVisible = !bIsDebugWindowVisible;
        DebugWindow->SetVisibility(bIsDebugWindowVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
    }
}

void AProjectAmeriaHUD::PrintCharaStatus()
{
    AProjectAmeriaGameMode* GameMode = Cast<AProjectAmeriaGameMode>(UGameplayStatics::GetGameMode(this));
    if (!GameMode) return;

    const TArray<AActor*>& AllCharacters = GameMode->GetAllCharacters();
    if (AllCharacters.Num() == 0) return;

    // キャラクター情報の表示
    AActor* CurrentCharacter = AllCharacters[CurrentCharacterIndex];
   if (IActionCharaInterface* CharInterface = Cast<IActionCharaInterface>(CurrentCharacter))
    {
       FString CharacterInfo = FString::Printf(
           TEXT("Name: %s\nEAffiliation: %s\nHP: %f\nMP: %f\nAP: %f\nSTR: %f\nDEF: %f\nMAG: %f\nRES: %f\nAGI: %f\nDEX: %f\nINT: %f\nCHA: %f\n"),
           *CharInterface->GetPlayerStats()->GetName(),
           *UEnum::GetValueAsString(CharInterface->GetAffiliation()),
           CharInterface->GetPlayerStats()->GetHealth(),
           CharInterface->GetPlayerStats()->GetMana(),
           CharInterface->GetCurrentActionPoints(),
           CharInterface->GetPlayerStats()->GetStrength(),
           CharInterface->GetPlayerStats()->GetEndurance(),
           CharInterface->GetPlayerStats()->GetMagicPower(),
           CharInterface->GetPlayerStats()->GetMagicResistance(),
           CharInterface->GetPlayerStats()->GetAgility(),
           CharInterface->GetPlayerStats()->GetDexterity(),
           CharInterface->GetPlayerStats()->GetIntelligence(),
           CharInterface->GetPlayerStats()->GetCharisma()
       );


        UpdateDebugText(CharacterInfo);
    }
    else
    {
        UpdateDebugText(TEXT("This character does not implement the ActionCharaInterface."));
    }


    // 次のキャラクターに移動
    CurrentCharacterIndex = (CurrentCharacterIndex + 1) % AllCharacters.Num();
}

void AProjectAmeriaHUD::PrintActionStats()
{
    UpdateDebugText(ActionDebugText);
}

void AProjectAmeriaHUD::BindActionDelegates(UActionBase* ActionBase)
{
    if (ActionBase)
    {
        ActionBase->OnActionExecuted.AddDynamic(this, &AProjectAmeriaHUD::OnActionExecuted);
    }
}

void AProjectAmeriaHUD::OnActionExecuted(AActor* Executor, AActor* Target)
{
    // デバッグ情報の更新ロジック
    //UpdateActionInfo(FActionInfo());
    FString state;
    if (AProjectAmeriaCharacter* AmeriaCharacter = Cast<AProjectAmeriaCharacter>(Executor)) {
        state = UUIUtility::PlayerStateToString(AmeriaCharacter->GetCurrentState());
    }

    ActionDebugText = FString::Printf(
        TEXT("ActionDebug\n%s\nExecuter : %s\nTarget : %s"),
        *state,
        *Executor->GetName(),
        *Target->GetName()
    );
}

void AProjectAmeriaHUD::UpdateActionInfo(const FActionInfo& ActionInfo)
{
   
}

void AProjectAmeriaHUD::ClearDebugText()
{
    CurrentDebugText = "";
}

void AProjectAmeriaHUD::UpdateDebugText(const FString& NewText)
{
    if (CurrentDebugText != NewText)
    {
        CurrentDebugText = NewText;
    }
}