// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BTTask_JumpAttack.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOMBATSYS_API UBTTask_JumpAttack : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

public:
	UBTTask_JumpAttack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UAnimMontage* JumpAttack;

	struct FTimerHandle CompleteAnimationTimerHandle;

	void OnAnimationComplete();
};
