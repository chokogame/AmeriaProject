// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NPC/Status/UnitStats.h"
#include "Logging/LogMacros.h"
#include "Action/ActionCharaInterface.h"
#include "Action/ActionBase.h"
#include "AmeriaDefine.h"
#include "ProjectAmeriaCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config = Game)
class AProjectAmeriaCharacter : public ACharacter, public IActionCharaInterface
{
    GENERATED_BODY()

public:
    AProjectAmeriaCharacter();

    /** ���t���[���Ă΂��֐� */
    virtual void Tick(float DeltaTime) override;

    /** ���͋@�\���o�C���h����֐� */
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    /** �v���C�J�n���ɌĂ΂��֐� */
    virtual void BeginPlay() override;

    /** �A�N�V���������s����֐� */
    virtual void ExecuteAction(UActionBase* Action) override;

    /** ���݂̍s���͂��擾����֐� */
    virtual float GetCurrentActionPoints() const override;

    /** �s���͂�����������֐� */
    virtual void DecreaseActionPoints(float Amount) override;

    /** �_���[�W���󂯂�֐� */
    virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

    /** UI�A�N�V�������\�b�h */
    UFUNCTION(BlueprintCallable, Category = "Actions")
        void AddAction(TSubclassOf<UActionBase> ActionClass);

    UFUNCTION(BlueprintCallable, Category = "Actions")
        void RemoveAction(TSubclassOf<UActionBase> ActionClass);

    UFUNCTION(BlueprintCallable, Category = "Actions")
        void Attack(const FInputActionValue& Value);

    /** �s���͂̃Q�b�^�[�ƃZ�b�^�[ */
    void SetCurrentActionPoints(float Points);
    float GetMaxActionPoints() const;
    void SetMaxActionPoints(float Points);

    /** �^�[���J�ڂ̓��͊֐� */
    void NextTurn();

    /** �X�e�[�^�X�̃Q�b�^�[�ƃZ�b�^�[ */
     // �X�e�[�^�X�ւ̃A�N�Z�X���\�b�h

    UUnitStats* GetPlayerStats() const { return PlayerStats; }

    /** �����̃Q�b�^�[�ƃZ�b�^�[ */
    virtual void SetAffiliation(EAffiliation NewAffiliation) override;
    virtual EAffiliation GetAffiliation() const override;

    /** �X�e�[�g�Ǘ� */
    FORCEINLINE EPlayerState GetCurrentState() const { return CurrentState; }

protected:
    /** �ړ����͂���������֐� */
    void Move(const FInputActionValue& Value);

    /** ���_���͂���������֐� */
    void Look(const FInputActionValue& Value);

    /** �Q�[�����[�h��؂�ւ���֐� */
    void ToggleGameMode();

    /** �^�[���x�[�X���[�h���ǂ������`�F�b�N����֐� */
    bool IsTurnBasedMode() const;

    /** �L�����N�^�[���s���\���ǂ������`�F�b�N����֐� */
    bool CanAct() const;

    /** �X�e�[�g�ύX����������֐� */
    void HandleIdleState();
    void HandleSelectingTargetState();
    void HandleAttackingState();
    void ChangeState(EPlayerState NewState);
    void SelectTarget();
    void ExecuteAttack();

    /** �A�N�V�����X���b�g */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actions")
        TArray<TSubclassOf<UActionBase>> ActionSlots;

    /** �v���C���[�X�e�[�^�X */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
        UUnitStats* PlayerStats;

    /** ���� */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Affiliation")
        EAffiliation Affiliation;

    /** �ő�s���� */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action Points", meta = (AllowPrivateAccess = "true"))
        float MaxActionPoints;

    /** ���݂̍s���� */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action Points", meta = (AllowPrivateAccess = "true"))
        float CurrentActionPoints;

private:
    /** �L�����N�^�[�̔w��ɃJ������z�u���邽�߂̃J�����u�[�� */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
        USpringArmComponent* CameraBoom;

    /** �t�H���[�J���� */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
        UCameraComponent* FollowCamera;

    /** �}�b�s���O�R���e�L�X�g */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
        UInputMappingContext* DefaultMappingContext;

    /** ���̓A�N�V���� */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
        UInputAction* JumpAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
        UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
        UInputAction* LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
        UInputAction* NextTurnAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
        UInputAction* ToggleModeAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
        UInputAction* SelectTargetAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
        UInputAction* AttackAction;

    /** �v���C���[�̏�� */
    EPlayerState CurrentState;

    /** ���݂̃^�[�Q�b�g */
    AActor* CurrentTarget;

    /** �^�[�Q�b�g�I�𒆂̃t���O */
    bool bIsSelectingTarget;

public:
    /** CameraBoom�T�u�I�u�W�F�N�g��Ԃ��֐� **/
    FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

    /** FollowCamera�T�u�I�u�W�F�N�g��Ԃ��֐� **/
    FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
