// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Action/ActionBase.h"
#include "AmeriaDefine.h"
#include "ActionCharaInterface.generated.h"

// �O���錾
class UUnitStats;

/**
 * �v���C���[��NPC�������A�N�V�������s�����߂̃C���^�[�t�F�[�X
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
    /** �A�N�V���������s���郁�\�b�h */
    virtual void ExecuteAction(UActionBase* Action) = 0;

    /** ���݂̍s���͂��擾���郁�\�b�h */
    virtual float GetCurrentActionPoints() const = 0;

    /** �s���͂����������郁�\�b�h */
    virtual void DecreaseActionPoints(float Amount) = 0;

    /** �X�e�[�^�X���擾���郁�\�b�h */
    virtual UUnitStats* GetPlayerStats() const = 0;  // �X�e�[�^�X�ւ̃A�N�Z�X���\�b�h

    /** �������擾���郁�\�b�h */
    virtual EAffiliation GetAffiliation() const = 0;

    /** ������ݒ肷�郁�\�b�h */
    virtual void SetAffiliation(EAffiliation NewAffiliation) = 0;
};

