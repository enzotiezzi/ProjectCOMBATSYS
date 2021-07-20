// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ETeams.h"
#include "GameFramework/Character.h"
#include "TankEnemy.generated.h"

UCLASS()
class PROJECTCOMBATSYS_API ATankEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATankEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UWidgetComponent* TeamIndicatorComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TEnumAsByte<ETeams> CurrentTeamName;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetTeam(TEnumAsByte<ETeams> Team1);
};
