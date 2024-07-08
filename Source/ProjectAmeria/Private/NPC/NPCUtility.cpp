#include "NPCUtility.h"
#include "NPCCharacter.h"  // ������NPCCharacter���C���N���[�h

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

// �_���[�W�v�Z�̊֐���ǉ�
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

    float AttackPower = bIsMagicAttack ? AttackerInterface->GetMagicPower() : AttackerInterface->GetStrength();
    float DefensePower = bIsMagicAttack ? DefenderInterface->GetResistance() : DefenderInterface->GetDefense();

    float Damage = (BasePower + (AttackPower * Multiplier)) - DefensePower;
    Damage = FMath::Max(0.0f, Damage); // �_���[�W���}�C�i�X�ɂȂ�Ȃ��悤�ɂ���

    // �_���[�W�v�Z�̏ڍׂ����O�ɏo��
    UE_LOG(LogTemp, Log, TEXT("CalculateDamage: Attacker: %s, Defender: %s"), *Attacker->GetName(), *Defender->GetName());
    UE_LOG(LogTemp, Log, TEXT("BasePower: %f, AttackPower: %f, Multiplier: %f, DefensePower: %f"), BasePower, AttackPower, Multiplier, DefensePower);
    UE_LOG(LogTemp, Log, TEXT("Calculated Damage: %f"), Damage);

    return Damage;
}
