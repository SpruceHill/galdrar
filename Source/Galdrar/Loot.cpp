// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "Loot.h"


// Sets default values
ALoot::ALoot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ALoot::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALoot::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

