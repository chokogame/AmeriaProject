// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjectAmeriaGameMode.h"
#include "ProjectAmeriaCharacter.h"
#include "NPC/NPCCharacter.h"
#include "EngineUtils.h"
#include "MyPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"


AProjectAmeriaGameMode::AProjectAmeriaGameMode()
{
	// set default pawn class to our Blueprinted character
    bIsTurnBasedMode = true;

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_Player"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
        PlayerControllerClass = AMyPlayerController::StaticClass();
	}
    static ConstructorHelpers::FClassFinder<AProjectAmeriaHUD> ProjectAmeriaHUD_BPClass(TEXT("/Game/UI/BP_ProjectAmeriaHUD"));
    if (ProjectAmeriaHUD_BPClass.Class != nullptr)
    {
        HUDClass = ProjectAmeriaHUD_BPClass.Class;
    }

    PrimaryActorTick.bCanEverTick = true; // Tickを有効にする
}

void AProjectAmeriaGameMode::BeginPlay()
{
    Super::BeginPlay();
    InitializeCharacters();
    StartTurn();

}

void AProjectAmeriaGameMode::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (bIsTurnBasedMode)
    {
        AProjectAmeriaHUD* HUD = GetProjectAmeriaHUD();
        if (HUD)
        {
            HUD->UpdateActionPointsUI();
        }
    }
}

void AProjectAmeriaGameMode::ToggleGameMode()
{
    bIsTurnBasedMode = !bIsTurnBasedMode;
    UE_LOG(LogTemp, Log, TEXT("Game Mode Toggled: %s"), bIsTurnBasedMode ? TEXT("Turn-Based") : TEXT("Free Movement"));
    if (bIsTurnBasedMode)
    {
        StartTurn();
    }

    AProjectAmeriaHUD* HUD = GetProjectAmeriaHUD();
    if (HUD)
    {
        HUD->UpdateTurnInfoUI(bIsTurnBasedMode, CurrentTurnState);
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
    CurrentTurnState = ETurnState::PlayerTurn;
    HandlePlayerTurn();
    bCanEndTurn = false;
   
    AProjectAmeriaHUD* HUD = GetProjectAmeriaHUD();
    if (HUD)
    {
        HUD->UpdateTurnInfoUI(bIsTurnBasedMode, CurrentTurnState);
        HUD->UpdateActionPointsUI();
    }
    else // エラーログ
    {
        UE_LOG(LogTemp, Warning, TEXT("HUD is nullptr"));
    }
}

void AProjectAmeriaGameMode::NextTurn()
{
    if (!bIsTurnBasedMode) return;

    switch (CurrentTurnState)
    {
    case  ETurnState::PlayerTurn:
        CurrentTurnState = ETurnState::AllyNPCTurn;
        HandleAllyNPCTurn();
        break;
    case  ETurnState::AllyNPCTurn:
        CurrentTurnState = ETurnState::EnemyNPCTurn;
        HandleEnemyNPCTurn();
        break;
    case  ETurnState::EnemyNPCTurn:
        CurrentTurnState = ETurnState::PlayerTurn;
      //  HandlePlayerTurn();
        StartTurn();
        break;
    }
    AProjectAmeriaHUD* HUD = GetProjectAmeriaHUD();
    if (HUD)
    {
        HUD->UpdateTurnInfoUI(bIsTurnBasedMode, CurrentTurnState);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("HUD is nullptr"));
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

void AProjectAmeriaGameMode::InitializeCharacters()
{
    AllCharacters.Empty();

    // プレイヤーキャラクターを取得
    AActor* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (PlayerCharacter)
    {
        AllCharacters.Add(PlayerCharacter);
    }
    else 
    {
        UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter is nullptr"));
    }

    // NPCキャラクターを取得
    TArray<AActor*> NPCCharacters;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), ANPCCharacter::StaticClass(), NPCCharacters);
    AllCharacters.Append(NPCCharacters);

    // 他のキャラクターを追加する処理があればここに追加
}

const TArray<AActor*>& AProjectAmeriaGameMode::GetAllCharacters() const
{
    return AllCharacters;
}

AProjectAmeriaHUD* AProjectAmeriaGameMode::GetProjectAmeriaHUD() const
{
    return Cast<AProjectAmeriaHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}