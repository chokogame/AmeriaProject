// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

void AMyPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    InputComponent->BindAction("ToggleTurnMode", IE_Pressed, this, &AMyPlayerController::ToggleTurnMode);
}

void AMyPlayerController::ToggleTurnMode()
{
    bIsTurnBasedMode = !bIsTurnBasedMode;

    // モード切り替え時の処理
}