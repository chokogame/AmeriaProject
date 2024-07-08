#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ActionBase.generated.h"

UCLASS(Abstract, Blueprintable)
class PROJECTAMERIA_API UActionBase : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Action")
        virtual void ExecuteAction(AActor* Executor);

    UFUNCTION(BlueprintCallable, Category = "Action")
        virtual float GetActionPointCost() const;
};

