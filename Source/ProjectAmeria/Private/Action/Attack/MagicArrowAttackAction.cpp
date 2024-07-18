// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/Attack/MagicArrowAttackAction.h"
#include "Action/ActionCharaInterface.h"
#include "../ProjectAmeriaGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h" // �ǉ�: UDecalComponent���g�p���邽�߂̃C���N���[�h
#include "GameFramework/ProjectileMovementComponent.h" // �ǉ�: UProjectileMovementComponent���g�p���邽�߂̃C���N���[�h
#include "NPC/NPCUtility.h"

UMagicArrowAttackAction::UMagicArrowAttackAction()
{
    ActionPointCost = 30.0f;
    DamageMultiplier = 1.0f;
    ProjectileSpawnOffset = 100.0f;
    BasePower = 5.0f; // �ǉ�: ��b�U���͂̏����l
    bIsMagicAttack = true; // �ǉ�: �f�t�H���g�ł͖��@�U���ɐݒ�
    PointerDecalMaterial = nullptr; // �f�t�H���g�ł̓f�J�[���f�ނ͐ݒ肵�Ȃ�
}

void UMagicArrowAttackAction::ExecuteAction(AActor* Executor, AActor* Target = nullptr)
{
    // ���N���X��ExecuteAction���Ăяo���A�f�o�b�O�\�������Z�b�g���܂��B
    Super::ExecuteAction(Executor, Target);

    if (IActionCharaInterface* Executable = Cast<IActionCharaInterface>(Executor))
    {
        if (Target == nullptr)
        {
            if (Executable->GetCurrentActionPoints() >= GetActionPointCost())
            {
                // �A�N�V�����̎��s���W�b�N
                FVector StartLocation = Executor->GetActorLocation();
                FVector ForwardVector = Executor->GetActorForwardVector();
                FVector EndLocation = StartLocation + (ForwardVector * ProjectileRange);
                // �f�o�b�O�\���F�g���[�X�̊J�n�ʒu�ƏI���ʒu�����O�ɕ\��
                UE_LOG(LogTemp, Log, TEXT("Tracing from %s to %s"), *StartLocation.ToString(), *EndLocation.ToString());

                // �f�o�b�O�\���F�g���[�X�̃��C����`��
                DrawDebugLine(Executor->GetWorld(), StartLocation, EndLocation, FColor::Green, true, -1.0f, 0, 5.0f);

                FHitResult HitResult;
                FCollisionQueryParams CollisionParams;
                CollisionParams.AddIgnoredActor(Executor);

                if (Executor->GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Pawn, CollisionParams))
                {

                    // �f�o�b�O�\���F�q�b�g�����ꏊ�Ƀ|�C���g��`��
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
                    // �|�C���^��\��
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
                            Decal->SetLifeSpan(1.0f); // �f�J�[����1�b��ɏ���
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
                    FVector SpawnLocation = Executor->GetActorLocation() + (ForwardVector * ProjectileSpawnOffset); // ���@�̑O���ɃI�t�Z�b�g
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