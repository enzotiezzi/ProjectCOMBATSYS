// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BTTask_StepBack.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOMBATSYS_API UBTTask_StepBack : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

public:
	UBTTask_StepBack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	struct FTimerHandle CompleteAnimationTimerHandle;
	void OnCompleteAnimation();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UAnimMontage* WalkBack;
};
