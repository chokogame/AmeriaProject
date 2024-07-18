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
        virtual void ExecuteAction(AActor* Executor, AActor* Target = nullptr);

    UFUNCTION(BlueprintCallable, Category = "Action")
        virtual float GetActionPointCost() const;

    // デリゲートを定義
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActionExecuted, AActor*, Executor, AActor*, Target);
    UPROPERTY(BlueprintAssignable, Category = "Events")
        FOnActionExecuted OnActionExecuted;
};

