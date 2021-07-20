// Fill out your copyright notice in the Description page of Project Settings.


#include "AITankEnemy.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "Perception/AIPerceptionComponent.h"

AAITankEnemy::AAITankEnemy()
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));

	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &AAITankEnemy::OnTargetPerceptionUpdated);
}

void AAITankEnemy::BeginPlay()
{
    Super::BeginPlay();

	if(BehaviorTree)
	{
		bool success = RunBehaviorTree(BehaviorTree);
	}
}

void AAITankEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AAITankEnemy::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if(Actor->ActorHasTag("Player"))
	{
		GEngine->AddOnScreenDebugMessage(rand(), 2, FColor::Cyan, "Achou");

		GetBlackboardComponent()->SetValueAsObject("Target", Actor);
	}
}