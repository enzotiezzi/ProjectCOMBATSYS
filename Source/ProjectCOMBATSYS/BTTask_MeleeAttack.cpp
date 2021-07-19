// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_MeleeAttack.h"

#include "AIController.h"
#include "GameFramework/Character.h"

UBTTask_MeleeAttack::UBTTask_MeleeAttack()
{
	
}

EBTNodeResult::Type UBTTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();

	ACharacter* Character = Cast<ACharacter>(ControlledPawn);

	if(Character)
	{
		GetWorld()->GetTimerManager().ClearTimer(CompleteAttackTimerHandle);
		
		class UAnimMontage* Attack = Attack1;
		
		int AttackIndex = FMath::RandRange(0, 1);

		switch(AttackIndex)
		{
			case 0:
				Attack = Attack1;
				break;
			case 1:
				Attack = Attack2;
				break;
		}

		Character->PlayAnimMontage(Attack);
		
		GetWorld()->GetTimerManager().SetTimer(CompleteAttackTimerHandle, this, &UBTTask_MeleeAttack::OnCompleteAttackAnimation, Attack->GetPlayLength());

		return EBTNodeResult::InProgress;
	}

	return EBTNodeResult::Failed;
}


void UBTTask_MeleeAttack::OnCompleteAttackAnimation()
{
	if(CompleteAttackTimerHandle.IsValid())
		GetWorld()->GetTimerManager().ClearTimer(CompleteAttackTimerHandle);

	FinishExecute(true);
}
