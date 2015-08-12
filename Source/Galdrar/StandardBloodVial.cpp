// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "StandardBloodVial.h"
#include "BaseCharacter.h"
#include "HUDAdapter.h"

// Sets default values for this component's properties
UStandardBloodVial::UStandardBloodVial()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;

	// 5 = Blood Vial, 0001 = ID
	ID = 50001;

	maxCharges = 5;
	charges = 0;

	healAmount = 20;
}


// Called when the game starts
void UStandardBloodVial::InitializeComponent()
{
	Super::InitializeComponent();

	// ...

}


// Called every frame
void UStandardBloodVial::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStandardBloodVial::Use()
{
	if (charges > 0)
	{
		charges -= 1;
		if (ABaseCharacter* character = dynamic_cast<ABaseCharacter*>(GetOwner()))
		{
			character->Heal(20);
		}
	}
	else
	{
		HUDAdapter HA;
		HA.Toast("Not enough charges");
	}
}
