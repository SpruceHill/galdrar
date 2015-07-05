// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "SpellEffect.h"


// Sets default values
ASpellEffect::ASpellEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBlueprint> DBprojectileBlueprint(TEXT("Blueprint'/Game/SpellEffects/GasCloudSpellEffect'"));
	if (DBprojectileBlueprint.Object)
	{
		GasCloudBluePrintReference = (UClass*)DBprojectileBlueprint.Object->GeneratedClass;
	}
}

// Called when the game starts or when spawned
void ASpellEffect::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpellEffect::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

