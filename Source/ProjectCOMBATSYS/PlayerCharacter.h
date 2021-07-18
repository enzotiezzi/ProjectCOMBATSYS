// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"

#include "PlayerCharacter.generated.h"

UCLASS()
class PROJECTCOMBATSYS_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* WeaponComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* ShieldComponent;
	
public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float AxisValue);
	void MoveSides(float AxisValue);
	
	void Attack();

	void SelectAttack();

	UFUNCTION(BlueprintCallable)
	void NextAttackCombo();

	UFUNCTION(BlueprintCallable)
	void Reset();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsAttacking = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool ContinueCombo = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int ComboCounter = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// attack animations
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Attack)
	class UAnimMontage* AttackCombo1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Attack)
	class UAnimMontage* AttackCombo2;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Attack)
	class UAnimMontage* AttackCombo3;
};