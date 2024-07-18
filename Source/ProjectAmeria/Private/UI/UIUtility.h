// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AmeriaDefine.h"
#include "UIUtility.generated.h"

/**
 * UI�ɂ܂�郆�[�e�B���e�B
 */
UCLASS()
class UUIUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
		static FString PlayerStateToString(EPlayerState State);

};
