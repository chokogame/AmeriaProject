#include "UnitStats.h"

// コンストラクタ
UUnitStats::UUnitStats()
{
    PrimaryComponentTick.bCanEverTick = false;

    Health = 100.0f;
    Mana = 50.0f;
    ActionPoints = 10.0f;
    Strength = 10.0f;
    Endurance = 10.0f;
    MagicPower = 10.0f;
    MagicResistance = 10.0f;
    Agility = 10.0f;
    Dexterity = 10.0f;
    Intelligence = 10.0f;
    Charisma = 10.0f;
}

// Healthのゲッター
float UUnitStats::GetHealth() const
{
    return Health;
}

// Healthのセッター
void UUnitStats::SetHealth(float Value)
{
    Health = Value;
}

// Manaのゲッター
float UUnitStats::GetMana() const
{
    return Mana;
}

// Manaのセッター
void UUnitStats::SetMana(float Value)
{
    Mana = Value;
}

// ActionPointsのゲッター
float UUnitStats::GetActionPoints() const
{
    return ActionPoints;
}

// ActionPointsのセッター
void UUnitStats::SetActionPoints(float Value)
{
    ActionPoints = Value;
}

// Strengthのゲッター
float UUnitStats::GetStrength() const
{
    return Strength;
}

// Strengthのセッター
void UUnitStats::SetStrength(float Value)
{
    Strength = Value;
}

// Enduranceのゲッター
float UUnitStats::GetEndurance() const
{
    return Endurance;
}

// Enduranceのセッター
void UUnitStats::SetEndurance(float Value)
{
    Endurance = Value;
}

// MagicPowerのゲッター
float UUnitStats::GetMagicPower() const
{
    return MagicPower;
}

// MagicPowerのセッター
void UUnitStats::SetMagicPower(float Value)
{
    MagicPower = Value;
}

// MagicResistanceのゲッター
float UUnitStats::GetMagicResistance() const
{
    return MagicResistance;
}

// MagicResistanceのセッター
void UUnitStats::SetMagicResistance(float Value)
{
    MagicResistance = Value;
}

// Agilityのゲッター
float UUnitStats::GetAgility() const
{
    return Agility;
}

// Agilityのセッター
void UUnitStats::SetAgility(float Value)
{
    Agility = Value;
}

// Dexterityのゲッター
float UUnitStats::GetDexterity() const
{
    return Dexterity;
}

// Dexterityのセッター
void UUnitStats::SetDexterity(float Value)
{
    Dexterity = Value;
}

// Intelligenceのゲッター
float UUnitStats::GetIntelligence() const
{
    return Intelligence;
}

// Intelligenceのセッター
void UUnitStats::SetIntelligence(float Value)
{
    Intelligence = Value;
}

// Charismaのゲッター
float UUnitStats::GetCharisma() const
{
    return Charisma;
}

// Charismaのセッター
void UUnitStats::SetCharisma(float Value)
{
    Charisma = Value;
}
