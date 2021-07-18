// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTGetRandomLocation.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOMBATSYS_API UBTTGetRandomLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTGetRandomLocation();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
