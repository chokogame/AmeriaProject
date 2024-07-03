#include "UnitStats.h"

// �R���X�g���N�^
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

// Health�̃Q�b�^�[
float UUnitStats::GetHealth() const
{
    return Health;
}

// Health�̃Z�b�^�[
void UUnitStats::SetHealth(float Value)
{
    Health = Value;
}

// Mana�̃Q�b�^�[
float UUnitStats::GetMana() const
{
    return Mana;
}

// Mana�̃Z�b�^�[
void UUnitStats::SetMana(float Value)
{
    Mana = Value;
}

// ActionPoints�̃Q�b�^�[
float UUnitStats::GetActionPoints() const
{
    return ActionPoints;
}

// ActionPoints�̃Z�b�^�[
void UUnitStats::SetActionPoints(float Value)
{
    ActionPoints = Value;
}

// Strength�̃Q�b�^�[
float UUnitStats::GetStrength() const
{
    return Strength;
}

// Strength�̃Z�b�^�[
void UUnitStats::SetStrength(float Value)
{
    Strength = Value;
}

// Endurance�̃Q�b�^�[
float UUnitStats::GetEndurance() const
{
    return Endurance;
}

// Endurance�̃Z�b�^�[
void UUnitStats::SetEndurance(float Value)
{
    Endurance = Value;
}

// MagicPower�̃Q�b�^�[
float UUnitStats::GetMagicPower() const
{
    return MagicPower;
}

// MagicPower�̃Z�b�^�[
void UUnitStats::SetMagicPower(float Value)
{
    MagicPower = Value;
}

// MagicResistance�̃Q�b�^�[
float UUnitStats::GetMagicResistance() const
{
    return MagicResistance;
}

// MagicResistance�̃Z�b�^�[
void UUnitStats::SetMagicResistance(float Value)
{
    MagicResistance = Value;
}

// Agility�̃Q�b�^�[
float UUnitStats::GetAgility() const
{
    return Agility;
}

// Agility�̃Z�b�^�[
void UUnitStats::SetAgility(float Value)
{
    Agility = Value;
}

// Dexterity�̃Q�b�^�[
float UUnitStats::GetDexterity() const
{
    return Dexterity;
}

// Dexterity�̃Z�b�^�[
void UUnitStats::SetDexterity(float Value)
{
    Dexterity = Value;
}

// Intelligence�̃Q�b�^�[
float UUnitStats::GetIntelligence() const
{
    return Intelligence;
}

// Intelligence�̃Z�b�^�[
void UUnitStats::SetIntelligence(float Value)
{
    Intelligence = Value;
}

// Charisma�̃Q�b�^�[
float UUnitStats::GetCharisma() const
{
    return Charisma;
}

// Charisma�̃Z�b�^�[
void UUnitStats::SetCharisma(float Value)
{
    Charisma = Value;
}
