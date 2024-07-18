#include "NPCUtility.h"
#include "NPCCharacter.h"  // ここでNPCCharacterをインクルード
#include "ProjectAmeria/ProjectAmeriaGameMode.h"
#include "Kismet/GameplayStatics.h"

void UNPCUtility::ChangeNPCsAffiliation(AActor* NPCActor, EAffiliation NewAffiliation)
{
    if (NPCActor)
    {
        ANPCCharacter* NPC = Cast<ANPCCharacter>(NPCActor);
        if (NPC)
        {
            NPC->SetAffiliation(NewAffiliation);
        }
    }
}

// ダメージ計算の関数を追加
float UNPCUtility::CalculateDamage(AActor* Attacker, AActor* Defender, float BasePower, float Multiplier, bool bIsMagicAttack)
{
    if (!Attacker || !Defender)
    {
        return 0.0f;
    }

    IActionCharaInterface* AttackerInterface = Cast<IActionCharaInterface>(Attacker);
    IActionCharaInterface* DefenderInterface = Cast<IActionCharaInterface>(Defender);

    if (!AttackerInterface || !DefenderInterface)
    {
        return 0.0f;
    }

    float AttackPower = bIsMagicAttack ? AttackerInterface->GetPlayerStats()->GetMagicPower() : AttackerInterface->GetPlayerStats()->GetStrength();
    float DefensePower = bIsMagicAttack ? DefenderInterface->GetPlayerStats()->GetMagicResistance() : DefenderInterface->GetPlayerStats()->GetEndurance();

    float Damage = (BasePower + (AttackPower * Multiplier)) - DefensePower;
    Damage = FMath::Max(0.0f, Damage); // ダメージがマイナスにならないようにする

    // ダメージ計算の詳細をログに出力
    UE_LOG(LogTemp, Log, TEXT("CalculateDamage: Attacker: %s, Defender: %s"), *Attacker->GetName(), *Defender->GetName());
    UE_LOG(LogTemp, Log, TEXT("BasePower: %f, AttackPower: %f, Multiplier: %f, DefensePower: %f"), BasePower, AttackPower, Multiplier, DefensePower);
    UE_LOG(LogTemp, Log, TEXT("Calculated Damage: %f"), Damage);

    return Damage;
}

//　キャラリストを取得
const TArray<AActor*>& UNPCUtility::GetAllCharacters(UObject* WorldContextObject)
{
    if (AProjectAmeriaGameMode* GameMode = Cast<AProjectAmeriaGameMode>(UGameplayStatics::GetGameMode(WorldContextObject)))
    {
        return GameMode->GetAllCharacters();
    }

    static TArray<AActor*> EmptyArray;
    return EmptyArray;
}

//　次のキャラを取得
AActor* UNPCUtility::GetNextCharacterByIndex(UObject* WorldContextObject, int32 CurrentIndex)
{
    if (AProjectAmeriaGameMode* GameMode = Cast<AProjectAmeriaGameMode>(UGameplayStatics::GetGameMode(WorldContextObject)))
    {
        const TArray<AActor*>& AllCharacters = GameMode->GetAllCharacters();

        if (AllCharacters.Num() == 0)
        {
            return nullptr;
        }

        int32 NextIndex = (CurrentIndex + 1) % AllCharacters.Num();
        return AllCharacters.IsValidIndex(NextIndex) ? AllCharacters[NextIndex] : nullptr;
    }

    return nullptr;
}