// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *�v���W�F�N�g���̐錾�N���X
 */

UENUM(BlueprintType)
enum class EPlayerState : uint8
{
    Idle UMETA(DisplayName = "Idle"),// �ҋ@���
    SelectingTarget UMETA(DisplayName = "SelectingTarget"),// �^�[�Q�b�g�I�����
    Attacking UMETA(DisplayName = "Attacking"),// �U�����
    // ���̏�Ԃ�ǉ�
};

// ������\��Enum
UENUM(BlueprintType)
enum class EAffiliation : uint8
{
	Neutral UMETA(DisplayName = "Neutral"),// ����
	Ally UMETA(DisplayName = "Ally"),// ����
	Enemy UMETA(DisplayName = "Enemy")// �G
};

// �^�[����Ԃ�\��Enum
UENUM(BlueprintType)
enum class ETurnState : uint8
{
    PlayerTurn UMETA(DisplayName = "Player Turn"), // �v���C���[�̃^�[��
    AllyNPCTurn UMETA(DisplayName = "Ally NPC Turn"), // ����NPC�̃^�[��
    EnemyNPCTurn UMETA(DisplayName = "Enemy NPC Turn") // �GNPC�̃^�[��
};


// �N���X���K�v�ȏꍇ�̂ݒ�`����
// �K�v���Ȃ��ꍇ�́A���̃N���X���폜
//class AmeriaDefine
//{
//public:
//    AmeriaDefine() = default;
//    ~AmeriaDefine() = default;
//};
