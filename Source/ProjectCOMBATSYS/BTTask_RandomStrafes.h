// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BTTask_RandomStrafes.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOMBATSYS_API UBTTask_RandomStrafes : public UBTTask_BlueprintBase
{
	GENERATED_BODY()
	
public:
	UBTTask_RandomStrafes();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UAnimMontage* RightStrafe;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UAnimMontage* LeftStrafe;

	struct FTimerHandle AnimCompleteTimerHandle;
	
	UFUNCTION()
	void OnAnimationCompleted();
};
