// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPC/Status/UnitStats.h"
#include "Action/ActionBase.h"
#include "Action/ActionCharaInterface.h"
#include "NPCCharacter.generated.h"

UENUM(BlueprintType)
enum class EAffiliation : uint8
{
	Neutral UMETA(DisplayName = "Neutral"),
	Ally UMETA(DisplayName = "Ally"),
	Enemy UMETA(DisplayName = "Enemy")
};

UCLASS()
class ANPCCharacter : public ACharacter, public IActionCharaInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPCCharacter();
	
	virtual void PerformAction();
	/// <summary>
	/// アクション関連関数群
	/// </summary>
	void SetCurrentActionPoints(float Points);
	float GetMaxActionPoints() const;
	void SetMaxActionPoints(float Points);
	virtual void ExecuteAction(UActionBase* Action) override;
	virtual float GetCurrentActionPoints() const override;
	/** 行動力を減少させる */
	virtual void DecreaseActionPoints(float Amount) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	UUnitStats* PlayerStats;

	//関係性
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Affiliation")
	EAffiliation Affiliation;

	void SetAffiliation(EAffiliation NewAffiliation);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** 行動できるかどうかをチェックする */
	bool CanAct() const;


private:
	/** 最大行動力 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action Points", meta = (AllowPrivateAccess = "true"))
		float MaxActionPoints;

	/** 現在の行動力 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action Points", meta = (AllowPrivateAccess = "true"))
		float CurrentActionPoints;

public:
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

};
