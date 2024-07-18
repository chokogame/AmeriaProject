// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Action/ActionBase.h"
#include "AmeriaDefine.h"
#include "ActionCharaInterface.generated.h"

// 前方宣言
class UUnitStats;

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
    /** アクションを実行するメソッド */
    virtual void ExecuteAction(UActionBase* Action) = 0;

    /** 現在の行動力を取得するメソッド */
    virtual float GetCurrentActionPoints() const = 0;

    /** 行動力を減少させるメソッド */
    virtual void DecreaseActionPoints(float Amount) = 0;

    /** ステータスを取得するメソッド */
    virtual UUnitStats* GetPlayerStats() const = 0;  // ステータスへのアクセスメソッド

    /** 所属を取得するメソッド */
    virtual EAffiliation GetAffiliation() const = 0;

    /** 所属を設定するメソッド */
    virtual void SetAffiliation(EAffiliation NewAffiliation) = 0;
};

