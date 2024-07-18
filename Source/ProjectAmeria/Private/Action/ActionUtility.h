// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ActionBase.h"
#include "ActionUtility.generated.h"

/**
 * �A�N�V�����֌W�̃��[�e�B���e�B�[
 */
UCLASS()
class UActionUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
		UFUNCTION(BlueprintCallable, Category = "Action")
		static UActionBase* CreateNewAction(UWorld* World, TSubclassOf<UActionBase> ActionClass);
};
