// Fill out your copyright notice in the Description page of Project Settings.


#include "UKillable.h"

TEnumAsByte<ETeams> IKillable::GetCurrentTeam()
{
	return this->CurrentTeam;
}

void IKillable::SetTeam(TEnumAsByte<ETeams> NewTeam, FString Title)
{
	
}
