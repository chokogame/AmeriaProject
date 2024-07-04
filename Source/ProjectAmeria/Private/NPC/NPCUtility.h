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
    UFUNCTION(BlueprintCallable, Category = "NPC")
    static void ChangeNPCsAffiliation(AActor* NPCActor, EAffiliation NewAffiliation);
    
};
