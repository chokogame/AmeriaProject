// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Action/ActionBase.h"
#include "ActionCharaInterface.generated.h"

/**
 * プレイヤーとNPCが同じアクションを行うためのインターフェース
 */
UINTERFACE(MinimalAPI)
class UActionCharaInterface : public UInterface
{
    GENERATED_BODY()
};

class PROJECTAMERIA_API IActionCharaInterface
{
    GENERATED_BODY()

public:
    virtual void ExecuteAction(UActionBase* Action) = 0;
    virtual float GetCurrentActionPoints() const = 0;
    virtual void DecreaseActionPoints(float Amount) = 0;

    //ステータス関連
    // ステータス取得の関数
    virtual float GetStrength() const = 0;
    virtual void SetStrength(float Value) = 0;
    virtual float GetMagicPower() const = 0;
    virtual void SetMagicPower(float Value) = 0;
    virtual float GetDefense() const = 0;
    virtual void SetDefense(float Value) = 0;
    virtual float GetResistance() const = 0;
    virtual void SetResistance(float Value) = 0;
    virtual float GetHealth() const = 0;
    virtual void SetHealth(float Value) = 0;
    virtual float GetMana() const = 0;
    virtual void SetMana(float Value) = 0;
    virtual float GetEndurance() const = 0;
    virtual void SetEndurance(float Value) = 0;
    virtual float GetAgility() const = 0;
    virtual void SetAgility(float Value) = 0;
    virtual float GetDexterity() const = 0;
    virtual void SetDexterity(float Value) = 0;
    virtual float GetIntelligence() const = 0;
    virtual void SetIntelligence(float Value) = 0;
    virtual float GetCharisma() const = 0;
    virtual void SetCharisma(float Value) = 0;

    // ダメージを受け取るための関数
    virtual void TakeDamage(float Damage) = 0;
};