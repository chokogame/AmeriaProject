// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/Attack/MagicArrowAttackAction.h"
#include "Action/ActionCharaInterface.h"
#include "../ProjectAmeriaGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h" // 追加: UDecalComponentを使用するためのインクルード
#include "GameFramework/ProjectileMovementComponent.h" // 追加: UProjectileMovementComponentを使用するためのインクルード
#include "NPC/NPCUtility.h"

UMagicArrowAttackAction::UMagicArrowAttackAction()
{
    ActionPointCost = 30.0f;
    DamageMultiplier = 1.0f;
    ProjectileSpawnOffset = 100.0f;
    BasePower = 5.0f; // 追加: 基礎攻撃力の初期値
    bIsMagicAttack = true; // 追加: デフォルトでは魔法攻撃に設定
    PointerDecalMaterial = nullptr; // デフォルトではデカール素材は設定しない
}

void UMagicArrowAttackAction::ExecuteAction(AActor* Executor, AActor* Target = nullptr)
{
    // 基底クラスのExecuteActionを呼び出し、デバッグ表示をリセットします。
    Super::ExecuteAction(Executor, Target);

    if (IActionCharaInterface* Executable = Cast<IActionCharaInterface>(Executor))
    {
        if (Target == nullptr)
        {
            if (Executable->GetCurrentActionPoints() >= GetActionPointCost())
            {
                // アクションの実行ロジック
                FVector StartLocation = Executor->GetActorLocation();
                FVector ForwardVector = Executor->GetActorForwardVector();
                FVector EndLocation = StartLocation + (ForwardVector * ProjectileRange);
                // デバッグ表示：トレースの開始位置と終了位置をログに表示
                UE_LOG(LogTemp, Log, TEXT("Tracing from %s to %s"), *StartLocation.ToString(), *EndLocation.ToString());

                // デバッグ表示：トレースのラインを描画
                DrawDebugLine(Executor->GetWorld(), StartLocation, EndLocation, FColor::Green, true, -1.0f, 0, 5.0f);

                FHitResult HitResult;
                FCollisionQueryParams CollisionParams;
                CollisionParams.AddIgnoredActor(Executor);

                if (Executor->GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Pawn, CollisionParams))
                {

                    // デバッグ表示：ヒットした場所にポイントを描画
                    DrawDebugPoint(Executor->GetWorld(), HitResult.Location, 10.0f, FColor::Red, true, -1.0f);
                    if (AActor* HitActor = HitResult.GetActor())
                    {
                        UE_LOG(LogTemp, Log, TEXT("Hit Actor: %s"), *HitActor->GetFName().ToString());
                        float Damage = 0.0f;

                        if (IActionCharaInterface* Character = Cast<IActionCharaInterface>(Executor))
                        {
                            Damage = UNPCUtility::CalculateDamage(Executor, HitActor, BasePower, DamageMultiplier, bIsMagicAttack);
                        }

                        UGameplayStatics::ApplyDamage(HitActor, Damage, Executor->GetInstigatorController(), Executor, nullptr);
                    }
                    // ポインタを表示
                    if (PointerDecalMaterial)
                    {
                        UDecalComponent* Decal = UGameplayStatics::SpawnDecalAtLocation(
                            Executor->GetWorld(),
                            PointerDecalMaterial,
                            FVector(10.0f, 10.0f, 10.0f),
                            HitResult.Location,
                            HitResult.ImpactNormal.Rotation()
                        );
                        if (Decal)
                        {
                            Decal->SetLifeSpan(1.0f); // デカールを1秒後に消す
                        }
                    }
                }

                Executable->DecreaseActionPoints(GetActionPointCost());

                if (Executable->GetCurrentActionPoints() <= 0)
                {
                    if (AProjectAmeriaGameMode* GameMode = Cast<AProjectAmeriaGameMode>(UGameplayStatics::GetGameMode(Executor)))
                    {
                        GameMode->NextTurn();
                    }
                }

                if (ProjectileClass)
                {
                    FVector SpawnLocation = Executor->GetActorLocation() + (ForwardVector * ProjectileSpawnOffset); // 自機の前方にオフセット
                    FRotator SpawnRotation = Executor->GetActorRotation();
                    Executor->GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnLocation, SpawnRotation);
                }
            }
        }
        else {

        }
      
    }
}


float UMagicArrowAttackAction::GetActionPointCost() const
{
    return ActionPointCost;
}