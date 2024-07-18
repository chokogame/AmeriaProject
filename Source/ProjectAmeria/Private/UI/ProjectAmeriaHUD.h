// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "../ProjectAmeriaCharacter.h"
#include "ProjectAmeriaHUD.generated.h"

enum class ETurnState : uint8;

/**
 * ゲームのHUDクラス
 */
UCLASS()
class AProjectAmeriaHUD : public AHUD
{
	GENERATED_BODY()

public:
	AProjectAmeriaHUD();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void UpdateTurnInfoUI(bool bIsTurnBasedMode, ETurnState CurrentTurnState);
	void UpdateActionPointsUI();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> TurnInfoWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> ActionPointsWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		FVector2D InitialWidgetPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		FVector2D WidgetOffset;

private:
	UPROPERTY()
		UUserWidget* TurnInfoWidget;

	UPROPERTY()
		TMap<ACharacter*, UUserWidget*> ActionPointsWidgets;

	void UpdateTextBlockPosition(UTextBlock* TextBlock, FVector2D Position);


/// <summary>
/// デバッグ用
/// </summary>
public:
	UFUNCTION(BlueprintCallable, Category = "Debug")
		void ToggleDebugWindow();
	UFUNCTION(BlueprintCallable, Category = "Debug")
		void PrintCharaStatus();
	UFUNCTION(BlueprintCallable, Category = "Debug")
		void PrintActionStats();
	UFUNCTION(BlueprintCallable, Category = "Debug")
		void ClearDebugText();

	// アクション情報を保持する構造体
	struct FActionInfo
	{
		FString ActionName;
		int32 APCost;
		int32 MPCost;
		float ActionPower;
		float Cooldown;
		float Range;
		float SuccessRate;
		FString ExecuterName;
		FString TargetName;
		FString BuffEffect;
		FString DebuffEffect;
	};
	//アクション情報の更新を求められたときのデリゲート
	UFUNCTION()
	void OnActionExecuted(AActor* Executor, AActor* Target);

	UFUNCTION(BlueprintCallable, Category = "Action")
		void BindActionDelegates(UActionBase* ActionBase);

	// デバッグ情報を更新する関数
	void UpdateActionInfo(const FActionInfo& ActionInfo);
private:
	UPROPERTY(EditAnywhere, Category = "Widgets")
	TSubclassOf<UUserWidget> DebugWindowClass;

	UPROPERTY()
	UUserWidget* DebugWindow;
	
	UPROPERTY()
	class UTextBlock* DebugText;
	
	bool bIsDebugWindowVisible;

	UFUNCTION()
	void UpdateDebugText(const FString& NewText);

	FString CurrentDebugText;

	FString ActionDebugText;

	int32 CurrentCharacterIndex;
};
