// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "ETeams.h"
#include "UAttacker.h"
#include "UKillable.h"
#include "GameFramework/Character.h"
#include "TankEnemy.generated.h"

UCLASS()
class PROJECTCOMBATSYS_API ATankEnemy : public ACharacter, public IKillable, public IAttacker
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATankEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USphereComponent* LeftHandSphereComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USphereComponent* RightHandSphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UWidgetComponent* TeamIndicatorComponent;
	
	struct FTimerHandle JumpAttackTimerHandle;
	void ResetJumpAttack();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float JumpAttackCooldown = 10.0f;

	class UBlackboardComponent* BlackBoardComponent;

	UFUNCTION()
	void OnAttackComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void SetTeam(TEnumAsByte<ETeams> NewTeam, FString Title) override;

protected:
	virtual void EnableLeftHandCollider_Implementation() override;
	
	virtual void EnableRightHandCollider_Implementation() override;
	
	virtual void DisableLeftHandCollider_Implementation() override;
	
	virtual void DisableRightHandCollider_Implementation() override;

	virtual void EnableColliders_Implementation() override;

	virtual void DisableColliders_Implementation() override;
};
