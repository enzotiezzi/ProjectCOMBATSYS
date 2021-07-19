// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BTTask_MeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOMBATSYS_API UBTTask_MeleeAttack : public UBTTask_BlueprintBase
{
	GENERATED_BODY()

public:
	UBTTask_MeleeAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	struct FTimerHandle CompleteAttackTimerHandle;
	void OnCompleteAttackAnimation();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UAnimMontage* Attack1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UAnimMontage* Attack2;
};
