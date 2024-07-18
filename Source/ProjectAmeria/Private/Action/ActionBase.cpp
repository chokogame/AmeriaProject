#include "ActionBase.h"
#include "../ProjectAmeriaCharacter.h"
#include <UI/ProjectAmeriaHUD.h>
#include <Kismet/GameplayStatics.h>

void UActionBase::ExecuteAction(AActor* Executor, AActor* Target /*= nullptr*/)
{
    // �h���N���X�����̊֐����I�[�o�[���C�h����K�v������܂��B
    // �f���Q�[�g�𔭉�
    OnActionExecuted.Broadcast(Executor, Target);

 }

float UActionBase::GetActionPointCost() const
{
    return 1.0f; // �f�t�H���g�̍s���|�C���g�R�X�g
}
