// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_StepBack.h"

#include "AIController.h"
#include "GameFramework/Character.h"

UBTTask_StepBack::UBTTask_StepBack()
{
	
}

EBTNodeResult::Type UBTTask_StepBack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();

	ACharacter* Character = Cast<ACharacter>(ControlledPawn);

	if(Character)
	{
		GetWorld()->GetTimerManager().ClearTimer(CompleteAnimationTimerHandle);

		int RandomNumber = FMath::RandRange(0, 100);

		if(RandomNumber <= 30)
			return EBTNodeResult::Succeeded;

		Character->PlayAnimMontage(WalkBack);

		GetWorld()->GetTimerManager().SetTimer(CompleteAnimationTimerHandle, this, &UBTTask_StepBack::OnCompleteAnimation, WalkBack->GetPlayLength());

		return EBTNodeResult::InProgress;
	}

	return EBTNodeResult::Failed;
}


void UBTTask_StepBack::OnCompleteAnimation()
{
	if(CompleteAnimationTimerHandle.IsValid())
		GetWorld()->GetTimerManager().ClearTimer(CompleteAnimationTimerHandle);

	FinishExecute(true);
}
