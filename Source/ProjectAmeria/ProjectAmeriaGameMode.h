// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UI/ProjectAmeriaHUD.h"
#include "ProjectAmeriaGameMode.generated.h"

UCLASS(minimalapi)
class AProjectAmeriaGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AProjectAmeriaGameMode();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override; // Tick�֐��̃I�[�o�[���C�h

    /** �^�[���ύX���� */
    void ToggleGameMode();  // ���[�h�؂�ւ��p���\�b�h
    void StartTurn();
    void NextTurn();
    void EndTurn();
    bool IsTurnBasedMode() const { return bIsTurnBasedMode; }
    void HandlePlayerTurn();
private:
    void HandleAllyNPCTurn();
    void HandleEnemyNPCTurn();
    bool bIsTurnBasedMode;
    bool bCanEndTurn;// �^�[���I���\���ǂ����������t���O

    ETurnState CurrentTurnState;

///�L�����N�^�[���֘A
public:
     // �S�L�����N�^�[�̃��X�g������������֐�
    void InitializeCharacters();

    // �S�L�����N�^�[�̃��X�g���擾����֐�
    const TArray<AActor*>& GetAllCharacters() const;


private:
    UPROPERTY()
    TArray<AActor*> AllCharacters;

    /// <summary>
    /// UI�֌W
    /// </summary>
public:
    AProjectAmeriaHUD* GetProjectAmeriaHUD() const;
};



