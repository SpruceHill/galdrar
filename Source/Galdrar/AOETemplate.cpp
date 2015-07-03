// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "AOETemplate.h"


// Sets default values
AAOETemplate::AAOETemplate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAOETemplate::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAOETemplate::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	GetOverlappingActors(affectedCharacters, ABaseCharacter::StaticClass());

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::FromInt(affectedCharacters.Num()));
}

