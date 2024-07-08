#include "ActionBase.h"
#include "../ProjectAmeriaCharacter.h"

void UActionBase::ExecuteAction(AActor* Executor)
{
    if (IActionCharaInterface* Executable = Cast<IActionCharaInterface>(Executor))
    {
        if (Executable->GetCurrentActionPoints() >= GetActionPointCost())
        {
            // アクションの実行ロジック
            Executable->DecreaseActionPoints(GetActionPointCost());
        }
    }
}

float UActionBase::GetActionPointCost() const
{
    return 1.0f; // デフォルトの行動ポイントコスト
}
