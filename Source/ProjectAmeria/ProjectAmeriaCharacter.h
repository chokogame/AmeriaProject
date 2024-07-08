// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPC/Status/UnitStats.h"
#include "Logging/LogMacros.h"
#include "Action/ActionCharaInterface.h"
#include "Action/ActionBase.h"
#include "ProjectAmeriaCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AProjectAmeriaCharacter : public ACharacter, public IActionCharaInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Next Turn Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* NextTurnAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ToggleModeAction;

	// AttackAction
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;

	UFUNCTION(BlueprintCallable, Category = "Actions")
		void AddAction(TSubclassOf<UActionBase> ActionClass);

	UFUNCTION(BlueprintCallable, Category = "Actions")
		void RemoveAction(TSubclassOf<UActionBase> ActionClass);

	UFUNCTION(BlueprintCallable, Category = "Actions")
	void Attack(const FInputActionValue& Value);

public:
	AProjectAmeriaCharacter();

/// <summary>
/// アクション関連関数群
/// </summary>
public:
	virtual void ExecuteAction(UActionBase* Action) override;
	virtual float GetCurrentActionPoints() const override;
	/** 行動力を減少させる */
	virtual void DecreaseActionPoints(float Amount) override;

	void SetCurrentActionPoints(float Points);
	float GetMaxActionPoints() const;
	void SetMaxActionPoints(float Points);

	/** ターン遷移を呼び出す入力関数 */
	void NextTurn();

	/** 現在セットされているアクション */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actions")
		TArray<TSubclassOf<UActionBase>> ActionSlots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	UUnitStats* PlayerStats;

	virtual void TakeDamage(float Damage) override;

	virtual float GetStrength() const override;
	virtual void SetStrength(float Value) override;
	virtual float GetMagicPower() const override;
	virtual void SetMagicPower(float Value) override;
	virtual float GetDefense() const override;
	virtual void SetDefense(float Value) override;
	virtual float GetResistance() const override;
	virtual void SetResistance(float Value) override;

	virtual float GetHealth() const override;
	virtual void SetHealth(float Value) override;
	virtual float GetMana() const override;
	virtual void SetMana(float Value) override;
	virtual float GetEndurance() const override;
	virtual void SetEndurance(float Value) override;
	virtual float GetAgility() const override;
	virtual void SetAgility(float Value) override;
	virtual float GetDexterity() const override;
	virtual void SetDexterity(float Value) override;
	virtual float GetIntelligence() const override;
	virtual void SetIntelligence(float Value) override;
	virtual float GetCharisma() const override;
	virtual void SetCharisma(float Value) override;

	

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);
			
	/** 行動できるかどうかをチェックする */
	bool CanAct() const;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// To add mapping context
	virtual void BeginPlay();

	void ToggleGameMode();  // モード切り替え用メソッド

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

private:
	/** 最大行動力 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action Points", meta = (AllowPrivateAccess = "true"))
		float MaxActionPoints;

	/** 現在の行動力 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action Points", meta = (AllowPrivateAccess = "true"))
		float CurrentActionPoints;

	bool IsTurnBasedMode() const;


};

