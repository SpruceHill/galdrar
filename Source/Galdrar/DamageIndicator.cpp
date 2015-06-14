// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "Engine/Blueprint.h"
#include "DamageIndicator.h"
#include "GaldrarColor.h"

ADamageIndicator::ADamageIndicator(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBlueprint> A3DDamageIndicator(TEXT("Blueprint'/Game/UI/3DDamageIndicator'"));
	if (A3DDamageIndicator.Object) {
		BlueprintVar = (UClass*)A3DDamageIndicator.Object->GeneratedClass;
	}
}

void ADamageIndicator::SetProperties(FVector position, float damage, DamageType type, bool crit)
{
	this->characterLocation = position;
	this->damage = damage;
	this->attackTypeColor = GaldrarColor::GetDamageTypeColor(type);
	this->crit = crit;
}

// Called when the game starts or when spawned
void ADamageIndicator::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "DI BEGIN PLAY");

	UWorld* World = GetWorld(); // get a reference to the world
	if (World) {
		// if world exists

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = Instigator;
		SpawnParams.bNoCollisionFail = true;

		//ADamageIndicator* DI = 
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "SPAWN BP ACTOR");
		World->SpawnActor<ADamageIndicator>(BlueprintVar, characterLocation, FRotator(0, 0, 0), SpawnParams);
	}	
}

// Called every frame
void ADamageIndicator::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

