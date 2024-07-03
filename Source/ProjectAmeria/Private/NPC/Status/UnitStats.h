#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/ActorComponent.h"
#include "UnitStats.generated.h"

// �X�e�[�^�X�N���X�B���ׂẴ��j�b�g�����ʂ��Ď��X�e�[�^�X���`����B
UCLASS(Blueprintable,ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTAMERIA_API UUnitStats : public UActorComponent
{
    GENERATED_BODY()

public:
    // �R���X�g���N�^
    UUnitStats();

    // Health�̃Q�b�^�[
    float GetHealth() const;
    // Health�̃Z�b�^�[
    void SetHealth(float Value);

    // Mana�̃Q�b�^�[
    float GetMana() const;
    // Mana�̃Z�b�^�[
    void SetMana(float Value);

    // ActionPoints�̃Q�b�^�[
    float GetActionPoints() const;
    // ActionPoints�̃Z�b�^�[
    void SetActionPoints(float Value);

    // Strength�̃Q�b�^�[
    float GetStrength() const;
    // Strength�̃Z�b�^�[
    void SetStrength(float Value);

    // Endurance�̃Q�b�^�[
    float GetEndurance() const;
    // Endurance�̃Z�b�^�[
    void SetEndurance(float Value);

    // MagicPower�̃Q�b�^�[
    float GetMagicPower() const;
    // MagicPower�̃Z�b�^�[
    void SetMagicPower(float Value);

    // MagicResistance�̃Q�b�^�[
    float GetMagicResistance() const;
    // MagicResistance�̃Z�b�^�[
    void SetMagicResistance(float Value);

    // Agility�̃Q�b�^�[
    float GetAgility() const;
    // Agility�̃Z�b�^�[
    void SetAgility(float Value);

    // Dexterity�̃Q�b�^�[
    float GetDexterity() const;
    // Dexterity�̃Z�b�^�[
    void SetDexterity(float Value);

    // Intelligence�̃Q�b�^�[
    float GetIntelligence() const;
    // Intelligence�̃Z�b�^�[
    void SetIntelligence(float Value);

    // Charisma�̃Q�b�^�[
    float GetCharisma() const;
    // Charisma�̃Z�b�^�[
    void SetCharisma(float Value);

protected:
    // Health�i���N�j
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float Health;

    // Mana�i���́j
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float Mana;

    // ActionPoints�i�s���́j
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float ActionPoints;

    // Strength�i�ؗ́j
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float Strength;

    // Endurance�i�ϋv�j
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float Endurance;

    // MagicPower�i���́j
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float MagicPower;

    // MagicResistance�i���@�h��j
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float MagicResistance;

    // Agility�i�r�q�j
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float Agility;

    // Dexterity�i��p�j
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float Dexterity;

    // Intelligence�i�m�́j
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float Intelligence;

    // Charisma�i���́j
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float Charisma;
};
