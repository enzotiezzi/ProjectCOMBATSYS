// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UAttacker.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UAttacker : public UInterface
{
	GENERATED_BODY()
};

class IAttacker
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EnableColliders();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EnableRightHandCollider();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void EnableLeftHandCollider();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DisableColliders();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DisableRightHandCollider();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void DisableLeftHandCollider();
};