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
    /** �R���X�g���N�^ */
    UUnitStats();

    /** ���O�̃Q�b�^�[ */
    FString GetName() const;
    /** ���O�̃Z�b�^�[ */
    void SetName(FString Value);

    /** Health�̃Q�b�^�[ */
    float GetHealth() const;
    /** Health�̃Z�b�^�[ */
    void SetHealth(float Value);

    /** Mana�̃Q�b�^�[ */
    float GetMana() const;
    /** Mana�̃Z�b�^�[ */
    void SetMana(float Value);

    /** �s���͂̃Q�b�^�[ */
    float GetActionPoints() const;
    /** �s���͂̃Z�b�^�[ */
    void SetActionPoints(float Value);

    /** �ؗ͂̃Q�b�^�[ */
    float GetStrength() const;
    /** �ؗ͂̃Z�b�^�[ */
    void SetStrength(float Value);

    /** �ϋv�͂̃Q�b�^�[ */
    float GetEndurance() const;
    /** �ϋv�͂̃Z�b�^�[ */
    void SetEndurance(float Value);

    /** ���͂̃Q�b�^�[ */
    float GetMagicPower() const;
    /** ���͂̃Z�b�^�[ */
    void SetMagicPower(float Value);

    /** ���@�h��͂̃Q�b�^�[ */
    float GetMagicResistance() const;
    /** ���@�h��͂̃Z�b�^�[ */
    void SetMagicResistance(float Value);

    /** �r�q���̃Q�b�^�[ */
    float GetAgility() const;
    /** �r�q���̃Z�b�^�[ */
    void SetAgility(float Value);

    /** ��p���̃Q�b�^�[ */
    float GetDexterity() const;
    /** ��p���̃Z�b�^�[ */
    void SetDexterity(float Value);

    /** �m�͂̃Q�b�^�[ */
    float GetIntelligence() const;
    /** �m�͂̃Z�b�^�[ */
    void SetIntelligence(float Value);

    /** ���͂̃Q�b�^�[ */
    float GetCharisma() const;
    /** ���͂̃Z�b�^�[ */
    void SetCharisma(float Value);

protected:
    /** ���O */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        FString Name;

    /** ���N */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float Health;

    /** ���� */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float Mana;

    /** �s���� */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float ActionPoints;

    /** �ؗ� */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float Strength;

    /** �ϋv�� */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float Endurance;

    /** ���� */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float MagicPower;

    /** ���@�h��� */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float MagicResistance;

    /** �r�q�� */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float Agility;

    /** ��p�� */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float Dexterity;

    /** �m�� */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float Intelligence;

    /** ���� */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float Charisma;
};
