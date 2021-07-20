// Fill out your copyright notice in the Description page of Project Settings.


#include "UKillable.h"

void IKillable::SetTeam(TEnumAsByte<ETeams> NewTeam)
{
	this->CurrentTeam = NewTeam;
}

TEnumAsByte<ETeams> IKillable::GetCurrentTeam()
{
	return this->CurrentTeam;
}
