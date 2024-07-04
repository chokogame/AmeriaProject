// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ProjectAmeriaGameMode.generated.h"

UCLASS(minimalapi)
class AProjectAmeriaGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AProjectAmeriaGameMode();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override; // Tick関数のオーバーライド

    void ToggleGameMode();  // モード切り替え用メソッド

    void StartTurn();
    void NextTurn();
    void EndTurn();

    bool IsTurnBasedMode() const { return bIsTurnBasedMode; }

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
        TSubclassOf<UUserWidget> TurnInfoWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
        TSubclassOf<UUserWidget> ActionPointsWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
        FVector2D InitialWidgetPosition;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
        FVector2D WidgetOffset;

    void HandlePlayerTurn();
private:
    void HandleAllyNPCTurn();
    void HandleEnemyNPCTurn();

    bool bIsTurnBasedMode;
    bool bCanEndTurn;  // ターン終了可能かどうかを示すフラグ

    enum ETurnState
    {
        PlayerTurn,
        AllyNPCTurn,
        EnemyNPCTurn
    };

    ETurnState CurrentTurnState;
    void UpdateTurnInfoUI();
    void UpdateActionPointsUI();
    void UpdateTextBlockPosition(UTextBlock* TextBlock, FVector2D Position);

    UPROPERTY()
        UUserWidget* TurnInfoWidget;

    UPROPERTY()
      TMap<ACharacter*, UUserWidget*> ActionPointsWidgets;
};



