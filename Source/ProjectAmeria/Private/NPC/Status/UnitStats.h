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
    /** コンストラクタ */
    UUnitStats();

    /** 名前のゲッター */
    FString GetName() const;
    /** 名前のセッター */
    void SetName(FString Value);

    /** Healthのゲッター */
    float GetHealth() const;
    /** Healthのセッター */
    void SetHealth(float Value);

    /** Manaのゲッター */
    float GetMana() const;
    /** Manaのセッター */
    void SetMana(float Value);

    /** 行動力のゲッター */
    float GetActionPoints() const;
    /** 行動力のセッター */
    void SetActionPoints(float Value);

    /** 筋力のゲッター */
    float GetStrength() const;
    /** 筋力のセッター */
    void SetStrength(float Value);

    /** 耐久力のゲッター */
    float GetEndurance() const;
    /** 耐久力のセッター */
    void SetEndurance(float Value);

    /** 魔力のゲッター */
    float GetMagicPower() const;
    /** 魔力のセッター */
    void SetMagicPower(float Value);

    /** 魔法防御力のゲッター */
    float GetMagicResistance() const;
    /** 魔法防御力のセッター */
    void SetMagicResistance(float Value);

    /** 俊敏性のゲッター */
    float GetAgility() const;
    /** 俊敏性のセッター */
    void SetAgility(float Value);

    /** 器用さのゲッター */
    float GetDexterity() const;
    /** 器用さのセッター */
    void SetDexterity(float Value);

    /** 知力のゲッター */
    float GetIntelligence() const;
    /** 知力のセッター */
    void SetIntelligence(float Value);

    /** 魅力のゲッター */
    float GetCharisma() const;
    /** 魅力のセッター */
    void SetCharisma(float Value);

protected:
    /** 名前 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        FString Name;

    /** 健康 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float Health;

    /** 魔力 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float Mana;

    /** 行動力 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float ActionPoints;

    /** 筋力 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float Strength;

    /** 耐久力 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float Endurance;

    /** 魔力 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float MagicPower;

    /** 魔法防御力 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float MagicResistance;

    /** 俊敏性 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float Agility;

    /** 器用さ */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float Dexterity;

    /** 知力 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float Intelligence;

    /** 魅力 */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats", meta = (AllowPrivateAccess = "true"))
        float Charisma;
};
