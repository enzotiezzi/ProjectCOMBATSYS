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

		if(success)
		{
			GetBlackboardComponent()->SetValueAsObject("SelfActor", this);
			GetBlackboardComponent()->SetValueAsVector("StartingLocation", GetCharacter()->GetActorLocation());
			GetBlackboardComponent()->SetValueAsBool("CanJumpAttack?", false);

			GetWorld()->GetTimerManager().SetTimer(JumpAttackTimerHandle, this, &AAITankEnemy::ResetJumpAttack, 5, true);
		}
	}
}

void AAITankEnemy::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	AActor* Target = Cast<AActor>(GetBlackboardComponent()->GetValueAsObject("Target"));

	if(Target)
	{
		FRotator LookAt = UKismetMathLibrary::FindLookAtRotation(GetPawn()->GetActorLocation(), Target->GetActorLocation());

		GetPawn()->SetActorRelativeRotation(LookAt);
	}
}

void AAITankEnemy::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if(Actor->ActorHasTag("Player"))
	{
		GEngine->AddOnScreenDebugMessage(rand(), 2, FColor::Cyan, "Achou");

		GetBlackboardComponent()->SetValueAsObject("Target", Actor);
	}
}

void AAITankEnemy::ResetJumpAttack()
{
	GEngine->AddOnScreenDebugMessage(rand(), 2, FColor::Cyan, "Reset Jump Attack");

	GetBlackboardComponent()->SetValueAsBool("CanJumpAttack?", true);
}
