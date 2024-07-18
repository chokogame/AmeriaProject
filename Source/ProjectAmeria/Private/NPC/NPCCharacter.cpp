// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCCharacter.h"

// Sets default values
ANPCCharacter::ANPCCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlayerStats = CreateDefaultSubobject<UUnitStats>(TEXT("NPCStats"));

}

// Called when the game starts or when spawned
void ANPCCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPCCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPCCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANPCCharacter::PerformAction()
{
	// NPCの行動ロジック
	if (CanAct())
	{
		// 行動ごとに1ポイント消費（例）
		DecreaseActionPoints(1.0f);
	}
}

void ANPCCharacter::DecreaseActionPoints(float Amount)
{
	CurrentActionPoints = FMath::Max(0.0f, CurrentActionPoints - Amount);
}

bool ANPCCharacter::CanAct() const
{
	return CurrentActionPoints > 0.0f;
}


float ANPCCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (ActualDamage > 0.0f)
	{
		float NewHealth = FMath::Max(0.0f, PlayerStats->GetHealth() - ActualDamage);
		PlayerStats->SetHealth(NewHealth);

		UE_LOG(LogTemp, Log, TEXT("%s : HP = %f"), *GetName(), PlayerStats->GetHealth());

		// Additional logic for when the character takes damage
		if (NewHealth <= 0)
		{
			// Handle character death
			UE_LOG(LogTemp, Log, TEXT("%s has died"), *GetName());
		}
	}

	return ActualDamage;
}

float ANPCCharacter::GetCurrentActionPoints() const
{
	return CurrentActionPoints;
}

void ANPCCharacter::ExecuteAction(UActionBase* Action)
{
	if (Action && CurrentActionPoints >= Action->GetActionPointCost())
	{
		Action->ExecuteAction(this);
	}
}


void ANPCCharacter::SetCurrentActionPoints(float Points)
{
	CurrentActionPoints = Points;
}

float ANPCCharacter::GetMaxActionPoints() const
{
	return MaxActionPoints;
}

void ANPCCharacter::SetMaxActionPoints(float Points)
{
	MaxActionPoints = Points;
}

void ANPCCharacter::SetAffiliation(EAffiliation NewAffiliation)
{
	Affiliation = NewAffiliation;
}

EAffiliation ANPCCharacter::GetAffiliation() const
{
	return EAffiliation();
}
