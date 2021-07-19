// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_JumpAttack.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"

UBTTask_JumpAttack::UBTTask_JumpAttack()
{
	
}

EBTNodeResult::Type UBTTask_JumpAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();

	ACharacter* Character = Cast<ACharacter>(ControlledPawn);

	if(Character)
	{
		if(CompleteAnimationTimerHandle.IsValid())
			GetWorld()->GetTimerManager().ClearTimer(CompleteAnimationTimerHandle);
		
		Character->PlayAnimMontage(JumpAttack);

		OwnerComp.GetBlackboardComponent()->SetValueAsBool("CanJumpAttack?", false);

		GetWorld()->GetTimerManager().SetTimer(CompleteAnimationTimerHandle, this, &UBTTask_JumpAttack::OnAnimationComplete, JumpAttack->GetPlayLength());

		return EBTNodeResult::InProgress;
	}

	return EBTNodeResult::Failed;
}

void UBTTask_JumpAttack::OnAnimationComplete()
{
	if(CompleteAnimationTimerHandle.IsValid())
		GetWorld()->GetTimerManager().ClearTimer(CompleteAnimationTimerHandle);

	FinishExecute(true);
}
