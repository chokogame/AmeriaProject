#include "ActionBase.h"
#include "../ProjectAmeriaCharacter.h"

void UActionBase::ExecuteAction(AActor* Executor)
{
    if (IActionCharaInterface* Executable = Cast<IActionCharaInterface>(Executor))
    {
        if (Executable->GetCurrentActionPoints() >= GetActionPointCost())
        {
            // �A�N�V�����̎��s���W�b�N
            Executable->DecreaseActionPoints(GetActionPointCost());
        }
    }
}

float UActionBase::GetActionPointCost() const
{
    return 1.0f; // �f�t�H���g�̍s���|�C���g�R�X�g
}
