// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "Aura.h"

// Sets default values
AAura::AAura()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAura::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAura::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

