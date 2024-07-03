// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPC/Status/UnitStats.h"
#include "NPCCharacter.generated.h"

UENUM(BlueprintType)
enum class EAffiliation : uint8
{
	Neutral UMETA(DisplayName = "Neutral"),
	Ally UMETA(DisplayName = "Ally"),
	Enemy UMETA(DisplayName = "Enemy")
};

UCLASS()
class ANPCCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPCCharacter();

	virtual void PerformAction();

	float GetCurrentActionPoints() const;
	void SetCurrentActionPoints(float Points);
	float GetMaxActionPoints() const;
	void SetMaxActionPoints(float Points);

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

	/** 行動力を減少させる */
	void DecreaseActionPoints(float Amount);

	/** 行動できるかどうかをチェックする */
	bool CanAct() const;


private:
	/** 最大行動力 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action Points", meta = (AllowPrivateAccess = "true"))
		float MaxActionPoints;

	/** 現在の行動力 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action Points", meta = (AllowPrivateAccess = "true"))
		float CurrentActionPoints;

};
