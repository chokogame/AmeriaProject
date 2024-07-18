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

// 名前のゲッター
FString UUnitStats::GetName() const
{
    return Name;
}

// 名前のセッター
void UUnitStats::SetName(FString Value)
{
    Name = Value;
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

// 行動力のゲッター
float UUnitStats::GetActionPoints() const
{
    return ActionPoints;
}

// 行動力のセッター
void UUnitStats::SetActionPoints(float Value)
{
    ActionPoints = Value;
}

// 筋力のゲッター
float UUnitStats::GetStrength() const
{
    return Strength;
}

// 筋力のセッター
void UUnitStats::SetStrength(float Value)
{
    Strength = Value;
}

// 耐久力のゲッター
float UUnitStats::GetEndurance() const
{
    return Endurance;
}

// 耐久力のセッター
void UUnitStats::SetEndurance(float Value)
{
    Endurance = Value;
}

// 魔力のゲッター
float UUnitStats::GetMagicPower() const
{
    return MagicPower;
}

// 魔力のセッター
void UUnitStats::SetMagicPower(float Value)
{
    MagicPower = Value;
}

// 魔法防御力のゲッター
float UUnitStats::GetMagicResistance() const
{
    return MagicResistance;
}

// 魔法防御力のセッター
void UUnitStats::SetMagicResistance(float Value)
{
    MagicResistance = Value;
}

// 俊敏性のゲッター
float UUnitStats::GetAgility() const
{
    return Agility;
}

// 俊敏性のセッター
void UUnitStats::SetAgility(float Value)
{
    Agility = Value;
}

// 器用さのゲッター
float UUnitStats::GetDexterity() const
{
    return Dexterity;
}

// 器用さのセッター
void UUnitStats::SetDexterity(float Value)
{
    Dexterity = Value;
}

// 知力のゲッター
float UUnitStats::GetIntelligence() const
{
    return Intelligence;
}

// 知力のセッター
void UUnitStats::SetIntelligence(float Value)
{
    Intelligence = Value;
}

// 魅力のゲッター
float UUnitStats::GetCharisma() const
{
    return Charisma;
}

// 魅力のセッター
void UUnitStats::SetCharisma(float Value)
{
    Charisma = Value;
}
