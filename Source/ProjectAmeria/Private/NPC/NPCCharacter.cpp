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

float ANPCCharacter::GetStrength() const
{
	return PlayerStats->GetStrength();
}

void ANPCCharacter::SetStrength(float Value)
{
	PlayerStats->SetStrength(Value);
}

float ANPCCharacter::GetMagicPower() const
{
	return PlayerStats->GetMagicPower();
}

void ANPCCharacter::SetMagicPower(float Value)
{
	PlayerStats->SetMagicPower(Value);
}

float ANPCCharacter::GetDefense() const
{
	return PlayerStats->GetEndurance();
}

void ANPCCharacter::SetDefense(float Value)
{
	PlayerStats->SetEndurance(Value);
}

float ANPCCharacter::GetResistance() const
{
	return PlayerStats->GetMagicResistance();
}

void ANPCCharacter::SetResistance(float Value)
{
	PlayerStats->SetMagicResistance(Value);
}

float ANPCCharacter::GetHealth() const
{
	return PlayerStats->GetHealth();
}

void ANPCCharacter::SetHealth(float Value)
{
	PlayerStats->SetHealth(Value);
}

float ANPCCharacter::GetMana() const
{
	return PlayerStats->GetMana();
}

void ANPCCharacter::SetMana(float Value)
{
	PlayerStats->SetMana(Value);
}

float ANPCCharacter::GetEndurance() const
{
	return PlayerStats->GetEndurance();
}

void ANPCCharacter::SetEndurance(float Value)
{
	PlayerStats->SetEndurance(Value);
}

float ANPCCharacter::GetAgility() const
{
	return PlayerStats->GetAgility();
}

void ANPCCharacter::SetAgility(float Value)
{
	PlayerStats->SetAgility(Value);
}

float ANPCCharacter::GetDexterity() const
{
	return PlayerStats->GetDexterity();
}

void ANPCCharacter::SetDexterity(float Value)
{
	PlayerStats->SetDexterity(Value);
}

float ANPCCharacter::GetIntelligence() const
{
	return PlayerStats->GetIntelligence();
}

void ANPCCharacter::SetIntelligence(float Value)
{
	PlayerStats->SetIntelligence(Value);
}

float ANPCCharacter::GetCharisma() const
{
	return PlayerStats->GetCharisma();
}

void ANPCCharacter::SetCharisma(float Value)
{
	PlayerStats->SetCharisma(Value);
}
