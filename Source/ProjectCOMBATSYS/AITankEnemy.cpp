// Fill out your copyright notice in the Description page of Project Settings.


#include "AITankEnemy.h"

#include "UKillable.h"
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
	UObject* ObjectTarget = GetBlackboardComponent()->GetValueAsObject("Target");

	if(!ObjectTarget)
	{
		IKillable* Enemy = Cast<IKillable>(Actor);

		if(Enemy)
		{
			IKillable* ControlledAI = Cast<IKillable>(GetPawn());

			if(ControlledAI)
			{
				if(ControlledAI->GetCurrentTeam() != Enemy->GetCurrentTeam())
				{
					GetBlackboardComponent()->SetValueAsObject("Target", Actor);
				}
			}
		}
	}
}