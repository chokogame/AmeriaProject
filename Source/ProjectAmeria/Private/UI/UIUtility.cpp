// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIUtility.h"

FString UUIUtility::PlayerStateToString(EPlayerState State)
{
    switch (State)
    {
    case EPlayerState::Idle:
        return TEXT("Idle");
    case EPlayerState::SelectingTarget:
        return TEXT("Selecting Target");
    case EPlayerState::Attacking:
        return TEXT("Attacking");
    default:
        return TEXT("Unknown");
    }
}
