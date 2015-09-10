// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "BaseTrait.h"


// Sets default values for this component's properties
UBaseTrait::UBaseTrait()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UBaseTrait::InitializeComponent()
{
	Super::InitializeComponent();

	// ...
	
}


// Called every frame
void UBaseTrait::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void UBaseTrait::ActivateTrait()
{

}

