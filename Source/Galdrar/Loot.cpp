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

	if (time > 0.f)
	{
		time -= DeltaTime;
	}
}

void ALoot::Activate(UCharacterStatsComponent* ownerStats, UCharacterStatsComponent* targetStats)
{

}

void ALoot::Disable()
{
	SetActorHiddenInGame(true);
	DisableComponentsSimulatePhysics();
	SetActorEnableCollision(false);
}

int32 ALoot::GetID() { return ID; }

bool ALoot::IsStackable(){ return bStackable; }
bool ALoot::IsActivatable(){ return bActivatable; }
float ALoot::GetWeight(){ return weight; }
