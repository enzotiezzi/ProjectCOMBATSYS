// Fill out your copyright notice in the Description page of Project Settings.


#include "TankEnemy.h"

#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ATankEnemy::ATankEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TeamIndicatorComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("TeamIndicatorComponent"));

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FQuat(FRotator(0.0f, -90.0f, 0.0f)));

	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetMesh()->SetCanEverAffectNavigation(true);

	TeamIndicatorComponent->SetupAttachment(GetRootComponent());	
}

// Called when the game starts or when spawned
void ATankEnemy::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void ATankEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATankEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

