// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"

#include "AITankEnemy.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTCOMBATSYS_API AAITankEnemy : public AAIController
{
	GENERATED_BODY()

public:
	AAITankEnemy();

	virtual void Tick(float DeltaSeconds) override;

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UAIPerceptionComponent* AIPerceptionComponent;

	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

};
