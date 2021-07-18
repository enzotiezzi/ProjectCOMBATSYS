// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTGetRandomLocation.h"

#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTGetRandomLocation::UBTTGetRandomLocation()
{
	
}

EBTNodeResult::Type UBTTGetRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FVector StartingLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector("StartingLocation");

	float radius = 300.0f;

	FNavLocation NewLocation;

	UNavigationSystemBase* NavigationSystemBase = GetWorld()->GetNavigationSystem();

	UNavigationSystemV1* NavigationSystemV1 = Cast<UNavigationSystemV1>(NavigationSystemBase);

	if(NavigationSystemV1)
	{
		bool success = NavigationSystemV1->GetRandomPointInNavigableRadius(StartingLocation, radius, NewLocation);

		if(success)
		{			
			OwnerComp.GetBlackboardComponent()->SetValueAsVector("NewLocation", NewLocation.Location);

			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}
