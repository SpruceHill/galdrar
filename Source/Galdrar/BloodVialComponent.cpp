// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "BloodVialComponent.h"
#include "BaseCharacter.h"


// Sets default values for this component's properties
UBloodVialComponent::UBloodVialComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBloodVialComponent::InitializeComponent()
{
	Super::InitializeComponent();

	// ...
	
}


// Called every frame
void UBloodVialComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UBloodVialComponent::Use()
{
	if (ABaseCharacter* character = dynamic_cast<ABaseCharacter*>(GetOwner()))
	{
		character->Heal(20);
	}
}

int32 UBloodVialComponent::GetMaxCharges() { return maxCharges; }
int32 UBloodVialComponent::GetCharges() { return charges; }
int32 UBloodVialComponent::GetID() { return ID; };

void UBloodVialComponent::AddCharges(int32 nbrOfCharges)
{
	if (charges + nbrOfCharges >= maxCharges)
	{
		charges = maxCharges;
	}
	else
	{
		charges += nbrOfCharges;
	}
}
