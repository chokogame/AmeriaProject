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

// ���O�̃Q�b�^�[
FString UUnitStats::GetName() const
{
    return Name;
}

// ���O�̃Z�b�^�[
void UUnitStats::SetName(FString Value)
{
    Name = Value;
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

// �s���͂̃Q�b�^�[
float UUnitStats::GetActionPoints() const
{
    return ActionPoints;
}

// �s���͂̃Z�b�^�[
void UUnitStats::SetActionPoints(float Value)
{
    ActionPoints = Value;
}

// �ؗ͂̃Q�b�^�[
float UUnitStats::GetStrength() const
{
    return Strength;
}

// �ؗ͂̃Z�b�^�[
void UUnitStats::SetStrength(float Value)
{
    Strength = Value;
}

// �ϋv�͂̃Q�b�^�[
float UUnitStats::GetEndurance() const
{
    return Endurance;
}

// �ϋv�͂̃Z�b�^�[
void UUnitStats::SetEndurance(float Value)
{
    Endurance = Value;
}

// ���͂̃Q�b�^�[
float UUnitStats::GetMagicPower() const
{
    return MagicPower;
}

// ���͂̃Z�b�^�[
void UUnitStats::SetMagicPower(float Value)
{
    MagicPower = Value;
}

// ���@�h��͂̃Q�b�^�[
float UUnitStats::GetMagicResistance() const
{
    return MagicResistance;
}

// ���@�h��͂̃Z�b�^�[
void UUnitStats::SetMagicResistance(float Value)
{
    MagicResistance = Value;
}

// �r�q���̃Q�b�^�[
float UUnitStats::GetAgility() const
{
    return Agility;
}

// �r�q���̃Z�b�^�[
void UUnitStats::SetAgility(float Value)
{
    Agility = Value;
}

// ��p���̃Q�b�^�[
float UUnitStats::GetDexterity() const
{
    return Dexterity;
}

// ��p���̃Z�b�^�[
void UUnitStats::SetDexterity(float Value)
{
    Dexterity = Value;
}

// �m�͂̃Q�b�^�[
float UUnitStats::GetIntelligence() const
{
    return Intelligence;
}

// �m�͂̃Z�b�^�[
void UUnitStats::SetIntelligence(float Value)
{
    Intelligence = Value;
}

// ���͂̃Q�b�^�[
float UUnitStats::GetCharisma() const
{
    return Charisma;
}

// ���͂̃Z�b�^�[
void UUnitStats::SetCharisma(float Value)
{
    Charisma = Value;
}
