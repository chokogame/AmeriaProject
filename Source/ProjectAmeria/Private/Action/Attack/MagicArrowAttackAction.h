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
        float BasePower; // 追加: 基礎攻撃力

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action")
        bool bIsMagicAttack; // 追加: 物理か魔法かを判断するフラグ

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
        TSubclassOf<class AActor> ProjectileClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
    float ProjectileSpawnOffset; // 発射位置のオフセット

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
    float ProjectileRange; // 射程距離

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
    UMaterialInterface* PointerDecalMaterial; // ポインタとして表示するデカール素材

   // virtual void ExecuteAction(AProjectAmeriaCharacter* Character) override;
    virtual void ExecuteAction(AActor* Executor, AActor* Target) override;
    virtual float GetActionPointCost() const override;

};
