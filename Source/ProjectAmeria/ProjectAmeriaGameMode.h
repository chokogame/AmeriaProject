// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UI/ProjectAmeriaHUD.h"
#include "ProjectAmeriaGameMode.generated.h"

UCLASS(minimalapi)
class AProjectAmeriaGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AProjectAmeriaGameMode();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override; // Tick関数のオーバーライド

    /** ターン変更処理 */
    void ToggleGameMode();  // モード切り替え用メソッド
    void StartTurn();
    void NextTurn();
    void EndTurn();
    bool IsTurnBasedMode() const { return bIsTurnBasedMode; }
    void HandlePlayerTurn();
private:
    void HandleAllyNPCTurn();
    void HandleEnemyNPCTurn();
    bool bIsTurnBasedMode;
    bool bCanEndTurn;// ターン終了可能かどうかを示すフラグ

    ETurnState CurrentTurnState;

///キャラクター情報関連
public:
     // 全キャラクターのリストを初期化する関数
    void InitializeCharacters();

    // 全キャラクターのリストを取得する関数
    const TArray<AActor*>& GetAllCharacters() const;


private:
    UPROPERTY()
    TArray<AActor*> AllCharacters;

    /// <summary>
    /// UI関係
    /// </summary>
public:
    AProjectAmeriaHUD* GetProjectAmeriaHUD() const;
};



