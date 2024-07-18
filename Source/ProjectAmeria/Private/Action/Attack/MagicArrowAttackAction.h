// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
#include "MagicArrowAttackAction.generated.h"

/**
 * 
 */
UCLASS()
class UMagicArrowAttackAction : public UActionBase
{
	GENERATED_BODY()
public:
    UMagicArrowAttackAction();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
        float ActionPointCost;


    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
        float DamageMultiplier;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
        float BasePower; // �ǉ�: ��b�U����

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
        bool bIsMagicAttack; // �ǉ�: ���������@���𔻒f����t���O

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
        TSubclassOf<class AActor> ProjectileClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
    float ProjectileSpawnOffset; // ���ˈʒu�̃I�t�Z�b�g

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
    float ProjectileRange; // �˒�����

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
    UMaterialInterface* PointerDecalMaterial; // �|�C���^�Ƃ��ĕ\������f�J�[���f��

   // virtual void ExecuteAction(AProjectAmeriaCharacter* Character) override;
    virtual void ExecuteAction(AActor* Executor, AActor* Target) override;
    virtual float GetActionPointCost() const override;

};
