// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *プロジェクト内の宣言クラス
 */

UENUM(BlueprintType)
enum class EPlayerState : uint8
{
    Idle UMETA(DisplayName = "Idle"),// 待機状態
    SelectingTarget UMETA(DisplayName = "SelectingTarget"),// ターゲット選択状態
    Attacking UMETA(DisplayName = "Attacking"),// 攻撃状態
    // 他の状態を追加
};

// 所属を表すEnum
UENUM(BlueprintType)
enum class EAffiliation : uint8
{
	Neutral UMETA(DisplayName = "Neutral"),// 中立
	Ally UMETA(DisplayName = "Ally"),// 味方
	Enemy UMETA(DisplayName = "Enemy")// 敵
};

// ターン状態を表すEnum
UENUM(BlueprintType)
enum class ETurnState : uint8
{
    PlayerTurn UMETA(DisplayName = "Player Turn"), // プレイヤーのターン
    AllyNPCTurn UMETA(DisplayName = "Ally NPC Turn"), // 味方NPCのターン
    EnemyNPCTurn UMETA(DisplayName = "Enemy NPC Turn") // 敵NPCのターン
};


// クラスが必要な場合のみ定義する
// 必要がない場合は、このクラスを削除
//class AmeriaDefine
//{
//public:
//    AmeriaDefine() = default;
//    ~AmeriaDefine() = default;
//};
