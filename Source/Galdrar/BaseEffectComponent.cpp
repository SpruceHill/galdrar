// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "BaseEffectComponent.h"


// Sets default values for this component's properties
UBaseEffectComponent::UBaseEffectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;

	bDefensive = false;
}


// Called when the game starts
void UBaseEffectComponent::InitializeComponent()
{
	Super::InitializeComponent();
	// ...
}


// Called every frame
void UBaseEffectComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

bool UBaseEffectComponent::IsDefensive()
{
	return bDefensive;
}
