// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "BaseArmorActor.h"


// Sets default values
ABaseArmorActor::ABaseArmorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseArmorActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseArmorActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}
