// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "NPCUtility.generated.h"

/**
 * NPC�ɂ܂�郆�[�e�B���e�B
 */
UCLASS()
class PROJECTAMERIA_API UNPCUtility : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    //�����̕ύX
    UFUNCTION(BlueprintCallable, Category = "NPC")
    static void ChangeNPCsAffiliation(AActor* NPCActor, EAffiliation NewAffiliation);

    // �_���[�W�v�Z�̊֐�
    UFUNCTION(BlueprintCallable, Category = "Damage")
    static float CalculateDamage(AActor* Attacker, AActor* Defender, float BasePower, float Multiplier, bool bIsMagicAttack);
    
    //�L�����ꗗ�̎擾
    UFUNCTION(BlueprintCallable, Category = "CharacterList")
    static const TArray<AActor*>& GetAllCharacters(UObject* WorldContextObject);

    //���̗v�f��Ԃ�
    UFUNCTION(BlueprintCallable, Category = "CharacterList")
    static AActor* GetNextCharacterByIndex(UObject* WorldContextObject, int32 CurrentIndex);
    
};
