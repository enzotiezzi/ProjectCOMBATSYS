// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AIController.h"
#include "GameFramework/Character.h"
#include "ETeams.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class PROJECTCOMBATSYS_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ETeams> SpawningTeam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnFrequency = 10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnRadius = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ACharacter> CharacterToSpawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	struct FTimerHandle SpawnTimerHandle;
	void OnSpawn();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
