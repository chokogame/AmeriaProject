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

    /** 毎フレーム呼ばれる関数 */
    virtual void Tick(float DeltaTime) override;

    /** 入力機能をバインドする関数 */
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    /** プレイ開始時に呼ばれる関数 */
    virtual void BeginPlay() override;

    /** アクションを実行する関数 */
    virtual void ExecuteAction(UActionBase* Action) override;

    /** 現在の行動力を取得する関数 */
    virtual float GetCurrentActionPoints() const override;

    /** 行動力を減少させる関数 */
    virtual void DecreaseActionPoints(float Amount) override;

    /** ダメージを受ける関数 */
    virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

    /** UIアクションメソッド */
    UFUNCTION(BlueprintCallable, Category = "Actions")
        void AddAction(TSubclassOf<UActionBase> ActionClass);

    UFUNCTION(BlueprintCallable, Category = "Actions")
        void RemoveAction(TSubclassOf<UActionBase> ActionClass);

    UFUNCTION(BlueprintCallable, Category = "Actions")
        void Attack(const FInputActionValue& Value);

    /** 行動力のゲッターとセッター */
    void SetCurrentActionPoints(float Points);
    float GetMaxActionPoints() const;
    void SetMaxActionPoints(float Points);

    /** ターン遷移の入力関数 */
    void NextTurn();

    /** ステータスのゲッターとセッター */
     // ステータスへのアクセスメソッド

    UUnitStats* GetPlayerStats() const { return PlayerStats; }

    /** 所属のゲッターとセッター */
    virtual void SetAffiliation(EAffiliation NewAffiliation) override;
    virtual EAffiliation GetAffiliation() const override;

    /** ステート管理 */
    FORCEINLINE EPlayerState GetCurrentState() const { return CurrentState; }

protected:
    /** 移動入力を処理する関数 */
    void Move(const FInputActionValue& Value);

    /** 視点入力を処理する関数 */
    void Look(const FInputActionValue& Value);

    /** ゲームモードを切り替える関数 */
    void ToggleGameMode();

    /** ターンベースモードかどうかをチェックする関数 */
    bool IsTurnBasedMode() const;

    /** キャラクターが行動可能かどうかをチェックする関数 */
    bool CanAct() const;

    /** ステート変更を処理する関数 */
    void HandleIdleState();
    void HandleSelectingTargetState();
    void HandleAttackingState();
    void ChangeState(EPlayerState NewState);
    void SelectTarget();
    void ExecuteAttack();

    /** アクションスロット */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Actions")
        TArray<TSubclassOf<UActionBase>> ActionSlots;

    /** プレイヤーステータス */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
        UUnitStats* PlayerStats;

    /** 所属 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Affiliation")
        EAffiliation Affiliation;

    /** 最大行動力 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action Points", meta = (AllowPrivateAccess = "true"))
        float MaxActionPoints;

    /** 現在の行動力 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Action Points", meta = (AllowPrivateAccess = "true"))
        float CurrentActionPoints;

private:
    /** キャラクターの背後にカメラを配置するためのカメラブーム */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
        USpringArmComponent* CameraBoom;

    /** フォローカメラ */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
        UCameraComponent* FollowCamera;

    /** マッピングコンテキスト */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
        UInputMappingContext* DefaultMappingContext;

    /** 入力アクション */
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

    /** プレイヤーの状態 */
    EPlayerState CurrentState;

    /** 現在のターゲット */
    AActor* CurrentTarget;

    /** ターゲット選択中のフラグ */
    bool bIsSelectingTarget;

public:
    /** CameraBoomサブオブジェクトを返す関数 **/
    FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

    /** FollowCameraサブオブジェクトを返す関数 **/
    FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
