#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/ActorComponent.h"
#include "UnitStats.generated.h"

// ステータスクラス。すべてのユニットが共通して持つステータスを定義する。
UCLASS(Blueprintable,ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTAMERIA_API UUnitStats : public UActorComponent
{
    GENERATED_BODY()

public:
    // コンストラクタ
    UUnitStats();

    // Healthのゲッター
    float GetHealth() const;
    // Healthのセッター
    void SetHealth(float Value);

    // Manaのゲッター
    float GetMana() const;
    // Manaのセッター
    void SetMana(float Value);

    // ActionPointsのゲッター
    float GetActionPoints() const;
    // ActionPointsのセッター
    void SetActionPoints(float Value);

    // Strengthのゲッター
    float GetStrength() const;
    // Strengthのセッター
    void SetStrength(float Value);

    // Enduranceのゲッター
    float GetEndurance() const;
    // Enduranceのセッター
    void SetEndurance(float Value);

    // MagicPowerのゲッター
    float GetMagicPower() const;
    // MagicPowerのセッター
    void SetMagicPower(float Value);

    // MagicResistanceのゲッター
    float GetMagicResistance() const;
    // MagicResistanceのセッター
    void SetMagicResistance(float Value);

    // Agilityのゲッター
    float GetAgility() const;
    // Agilityのセッター
    void SetAgility(float Value);

    // Dexterityのゲッター
    float GetDexterity() const;
    // Dexterityのセッター
    void SetDexterity(float Value);

    // Intelligenceのゲッター
    float GetIntelligence() const;
    // Intelligenceのセッター
    void SetIntelligence(float Value);

    // Charismaのゲッター
    float GetCharisma() const;
    // Charismaのセッター
    void SetCharisma(float Value);

protected:
    // Health（健康）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float Health;

    // Mana（魔力）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float Mana;

    // ActionPoints（行動力）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float ActionPoints;

    // Strength（筋力）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float Strength;

    // Endurance（耐久）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float Endurance;

    // MagicPower（魔力）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float MagicPower;

    // MagicResistance（魔法防御）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float MagicResistance;

    // Agility（俊敏）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float Agility;

    // Dexterity（器用）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float Dexterity;

    // Intelligence（知力）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float Intelligence;

    // Charisma（魅力）
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float Charisma;
};
