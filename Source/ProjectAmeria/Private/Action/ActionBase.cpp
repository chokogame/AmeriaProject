#include "ActionBase.h"
#include "../ProjectAmeriaCharacter.h"
#include <UI/ProjectAmeriaHUD.h>
#include <Kismet/GameplayStatics.h>

void UActionBase::ExecuteAction(AActor* Executor, AActor* Target /*= nullptr*/)
{
    // 派生クラスがこの関数をオーバーライドする必要があります。
    // デリゲートを発火
    OnActionExecuted.Broadcast(Executor, Target);

 }

float UActionBase::GetActionPointCost() const
{
    return 1.0f; // デフォルトの行動ポイントコスト
}
