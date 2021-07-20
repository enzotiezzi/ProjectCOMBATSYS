// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"

#include <string>

#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectCOMBATSYS/TankEnemy.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &ASpawner::OnSpawn, SpawnFrequency, true);
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

void ASpawner::OnSpawn()
{
	UNavigationSystemBase* NavigationSystemBase = GetWorld()->GetNavigationSystem();

	UNavigationSystemV1* NavigationSystemV1 = Cast<UNavigationSystemV1>(NavigationSystemBase);

	if(NavigationSystemV1)
	{
		FNavLocation NewLocation;

		bool success = NavigationSystemV1->GetRandomPointInNavigableRadius(GetActorLocation(), SpawnRadius, NewLocation);

		if(success)
		{
			GEngine->AddOnScreenDebugMessage(rand(), 2, FColor::Cyan, "New Location");

			FActorSpawnParameters SpawnParameters;
			
			AActor* SpawnedActor = GetWorld()->SpawnActor<ACharacter>(CharacterToSpawn, NewLocation.Location, GetActorRotation(), SpawnParameters);

			if(SpawnedActor)
			{
				IKillable* Enemy = Cast<IKillable>(SpawnedActor);

				if(Enemy)
				{
					GEngine->AddOnScreenDebugMessage(rand(), 2, FColor::Cyan, "Spawn");

					Index++;
					
					Enemy->SetTeam(SpawningTeam, FString::FromInt(Index));
				}
			}
		}
	}
}
