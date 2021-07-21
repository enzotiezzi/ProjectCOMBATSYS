// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_RandomStrafes.h"

#include "AIController.h"
#include "GameFramework/Character.h"

UBTTask_RandomStrafes::UBTTask_RandomStrafes()
{
	
}

EBTNodeResult::Type UBTTask_RandomStrafes::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* Owner = OwnerComp.GetAIOwner()->GetPawn();

	ACharacter* Character = Cast<ACharacter>(Owner);

	if(Character)
	{
		bool strafeSide = rand() % 2 == 0;
		
		UAnimMontage* ChosenMontage;

		if(strafeSide)
			ChosenMontage = RightStrafe;
		else
			ChosenMontage = LeftStrafe;

		Character->PlayAnimMontage(ChosenMontage);
		
		GetWorld()->GetTimerManager().SetTimer(AnimCompleteTimerHandle, this, &UBTTask_RandomStrafes::OnAnimationCompleted, ChosenMontage->GetPlayLength(), false);

		return EBTNodeResult::InProgress;
	}
	
	return EBTNodeResult::Failed;
}

void UBTTask_RandomStrafes::OnAnimationCompleted()
{
	if(AnimCompleteTimerHandle.IsValid())
		GetWorld()->GetTimerManager().ClearTimer(AnimCompleteTimerHandle);
	
	FinishExecute(true);
}
