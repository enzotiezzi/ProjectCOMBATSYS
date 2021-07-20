// Fill out your copyright notice in the Description page of Project Settings.


#include "TankEnemy.h"

#include "Components/TextBlock.h"
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

	SetTeam(ETeams::BLUE);
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

void ATankEnemy::SetTeam(TEnumAsByte<ETeams> Team)
{
	this->CurrentTeamName = Team;

	UUserWidget* Widget = TeamIndicatorComponent->GetWidget();

	if(Widget)
	{
		UTextBlock* TextBlockTeam = Cast<UTextBlock>(Widget->GetWidgetFromName(TEXT("T_TeamColor")));
		
		if(TextBlockTeam)
		{
			FText TeamText;
			FSlateColor TeamColor;
			
			if(Team == ETeams::BLUE)
			{
				TeamText = FText::FromString("TEAM BLUE");
				TeamColor = FSlateColor(FColor::Cyan);
			}
			else
			{
				TeamText = FText::FromString("TEAM RED");
				TeamColor = FSlateColor(FColor::Red);
			}

			TextBlockTeam->SetText(TeamText);
			TextBlockTeam->SetColorAndOpacity(TeamColor);
		}
	}
}
