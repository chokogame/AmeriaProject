// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPC/Status/UnitStats.h"
#include "Action/ActionBase.h"
#include "AmeriaDefine.h"
#include "Action/ActionCharaInterface.h"
#include "NPCCharacter.generated.h"

UCLASS()
class ANPCCharacter : public ACharacter, public IActionCharaInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANPCCharacter();
	
	virtual void PerformAction();
	/// <summary>
	/// �A�N�V�����֘A�֐��Q
	/// </summary>
	void SetCurrentActionPoints(float Points);
	float GetMaxActionPoints() const;
	void SetMaxActionPoints(float Points);
	virtual void ExecuteAction(UActionBase* Action) override;
	virtual float GetCurrentActionPoints() const override;
	/** �s���͂����������� */
	virtual void DecreaseActionPoints(float Amount) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	UUnitStats* PlayerStats;

	//�֌W��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Affiliation")
	EAffiliation Affiliation;

	void SetAffiliation(EAffiliation NewAffiliation) override;

	EAffiliation GetAffiliation() const override;

	UUnitStats* GetPlayerStats() const { return PlayerStats; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** �s���ł��邩�ǂ������`�F�b�N���� */
	bool CanAct() const;


private:
	/** �ő�s���� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action Points", meta = (AllowPrivateAccess = "true"))
		float MaxActionPoints;

	/** ���݂̍s���� */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action Points", meta = (AllowPrivateAccess = "true"))
		float CurrentActionPoints;

public:
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

};
