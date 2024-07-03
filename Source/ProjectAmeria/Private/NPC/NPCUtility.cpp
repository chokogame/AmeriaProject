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


