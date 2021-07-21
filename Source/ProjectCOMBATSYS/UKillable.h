// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ETeams.h"
#include "UKillable.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UKillable : public UInterface
{
	GENERATED_BODY()
};

class IKillable
{
	GENERATED_BODY()

public:
	virtual void SetTeam(TEnumAsByte<ETeams> NewTeam, FString Title);
	
	TEnumAsByte<ETeams> GetCurrentTeam();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	float ReceiveDamage(float AmountOfDamage);

protected:
	TEnumAsByte<ETeams> CurrentTeam;
};
