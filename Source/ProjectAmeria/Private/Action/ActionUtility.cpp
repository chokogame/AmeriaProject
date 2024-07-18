// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/ActionUtility.h"
#include "UI/ProjectAmeriaHUD.h"
#include "Kismet/GameplayStatics.h"

UActionBase* UActionUtility::CreateNewAction(UWorld* World, TSubclassOf<UActionBase> ActionClass)
{
    if (!World || !*ActionClass)
    {
        return nullptr;
    }

    UActionBase* NewAction = NewObject<UActionBase>(World, ActionClass);

    // アクションが生成されたことをHUDに通知
    if (AProjectAmeriaHUD* HUD = Cast<AProjectAmeriaHUD>(UGameplayStatics::GetPlayerController(World, 0)->GetHUD()))
    {
        HUD->BindActionDelegates(NewAction);
    }

    return NewAction;
}
