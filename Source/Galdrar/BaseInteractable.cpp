// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "BaseInteractable.h"


// Sets default values
ABaseInteractable::ABaseInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABaseInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseInteractable::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

FString ABaseInteractable::GetName(){ return name; }
FString ABaseInteractable::GetDesc(){ return desc; }

UPrimitiveComponent* ABaseInteractable::GetMesh()
{
	return mesh;
}

void ABaseInteractable::SetMesh(UPrimitiveComponent* newMesh)
{
	mesh = newMesh;
}
