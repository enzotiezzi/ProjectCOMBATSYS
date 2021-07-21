// Fill out your copyright notice in the Description page of Project Settings.


#include "TankEnemy.h"

#include "AITankEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/TextBlock.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ATankEnemy::ATankEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TeamIndicatorComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("TeamIndicatorComponent"));
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	LeftHandSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("LeftHandSphereComponent"));
	RightHandSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RightHandSphereComponent"));

	TeamIndicatorComponent->SetupAttachment(GetRootComponent());
	BoxComponent->SetupAttachment(GetRootComponent());
	LeftHandSphereComponent->SetupAttachment(GetMesh(), "LeftHandSocket");
	RightHandSphereComponent->SetupAttachment(GetMesh(), "RightHandSocket");

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -90.0f), FQuat(FRotator(0.0f, -90.0f, 0.0f)));
	BoxComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 30.0f));
	
	LeftHandSphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightHandSphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RightHandSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ATankEnemy::OnAttackComponentBeginOverlap);
	LeftHandSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ATankEnemy::OnAttackComponentBeginOverlap);

	GetCharacterMovement()->bOrientRotationToMovement = true;

	GetMesh()->SetCanEverAffectNavigation(true);
}

// Called when the game starts or when spawned
void ATankEnemy::BeginPlay()
{
	Super::BeginPlay();

	AController* MyController = GetController();

	if(MyController)
	{
		AAITankEnemy* AIController = Cast<AAITankEnemy>(MyController);

		if(AIController)
		{
			BlackBoardComponent = AIController->GetBlackboardComponent();

			BlackBoardComponent->SetValueAsObject("SelfActor", this);
			BlackBoardComponent->SetValueAsVector("StartingLocation", GetActorLocation());
			BlackBoardComponent->SetValueAsBool("CanJumpAttack?", false);

			GetWorld()->GetTimerManager().SetTimer(JumpAttackTimerHandle, this, &ATankEnemy::ResetJumpAttack, JumpAttackCooldown, true);
		}
	}
}

// Called every frame
void ATankEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UObject* ObjectTarget = BlackBoardComponent->GetValueAsObject("Target");

	if(ObjectTarget)
	{
		AActor* Target = Cast<AActor>(ObjectTarget);

		if(Target)
		{
			FRotator LookAt = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), Target->GetActorLocation());

			SetActorRelativeRotation(LookAt);
		}
	}
}

void ATankEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void ATankEnemy::SetTeam(TEnumAsByte<ETeams> Team, FString Title)
{
	CurrentTeam = Team;

	UUserWidget* Widget = TeamIndicatorComponent->GetWidget();

	if(Widget)
	{
		UTextBlock* TextBlockTeam = Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("T_TeamColor")));
		
		if(TextBlockTeam)
		{
			FSlateColor TeamColor;
			
			if(Team == ETeams::BLUE)
				TeamColor = FSlateColor(FColor::Cyan);
			else
				TeamColor = FSlateColor(FColor::Red);

			TextBlockTeam->SetText(FText::FromString(Title));
			TextBlockTeam->SetColorAndOpacity(TeamColor);
		}
	}
}

void ATankEnemy::ResetJumpAttack()
{
	GEngine->AddOnScreenDebugMessage(rand(), 2, FColor::Cyan, "Reset Jump Attack");

	if(BlackBoardComponent)
		BlackBoardComponent->SetValueAsBool("CanJumpAttack?", true);
}

void ATankEnemy::OnAttackComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IKillable* Killable = Cast<IKillable>(OtherActor);

	if(Killable)
	{
		if(CurrentTeam != Killable->GetCurrentTeam())
		{
			
		}
	}
}

void ATankEnemy::EnableLeftHandCollider_Implementation()
{
	this->LeftHandSphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ATankEnemy::EnableRightHandCollider_Implementation()
{
	this->RightHandSphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void ATankEnemy::DisableLeftHandCollider_Implementation()
{
	this->LeftHandSphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ATankEnemy::DisableRightHandCollider_Implementation()
{
	this->RightHandSphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ATankEnemy::EnableColliders_Implementation()
{
	EnableLeftHandCollider_Implementation();
	EnableRightHandCollider_Implementation();
}

void ATankEnemy::DisableColliders_Implementation()
{
	DisableLeftHandCollider_Implementation();
	DisableRightHandCollider_Implementation();
}
