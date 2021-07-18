// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->bUseControllerRotationYaw = false;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	WeaponComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponComponent"));
	ShieldComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShieldComponent"));

	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	SpringArmComponent->SetupAttachment(GetMesh());

	WeaponComponent->SetupAttachment(GetMesh(), TEXT("SwordSocket"));
	ShieldComponent->SetupAttachment(GetMesh(), TEXT("ShieldSocket"));

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FQuat(FRotator(0.0f, -90.0f, 0.0f)));

	GetCharacterMovement()->bOrientRotationToMovement = true;
	SpringArmComponent->bUsePawnControlRotation = true;

	this->Tags.Add("Player");
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveSides", this, &APlayerCharacter::MoveSides);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerCharacter::Attack);
}

void APlayerCharacter::MoveForward(float AxisValue)
{
	if(Controller != nullptr && AxisValue != 0.0f)
	{
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, AxisValue);
	}
}

void APlayerCharacter::MoveSides(float AxisValue)
{
	if(Controller != nullptr && AxisValue != 0.0f)
	{
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(Direction, AxisValue);
	}
}

void APlayerCharacter::Attack()
{
	if(IsAttacking)
		ContinueCombo = true;
	else
	{
		IsAttacking = true;

		SelectAttack();
	}
}

void APlayerCharacter::Reset()
{
	IsAttacking = false;
	ContinueCombo = false;
	ComboCounter = 0;
}

void APlayerCharacter::NextAttackCombo()
{
	if(ContinueCombo)
	{
		ContinueCombo = false;

		SelectAttack();
	}
}

void APlayerCharacter::SelectAttack()
{	
	switch (ComboCounter)
	{
		case 0:
			ComboCounter = 1;
			PlayAnimMontage(AttackCombo1);
			break;
		case 1:
			ComboCounter = 2;
			PlayAnimMontage(AttackCombo2);
			break;
		case 2:
			ComboCounter = 0;
			PlayAnimMontage(AttackCombo3);
			break;
	}
}