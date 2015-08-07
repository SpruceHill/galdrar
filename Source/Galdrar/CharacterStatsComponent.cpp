// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "CharacterStatsComponent.h"


// Sets default values for this component's properties
UCharacterStatsComponent::UCharacterStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = false;

	/* COMBAT STATS */
	defaultMaxHealth = 100.f;
	maxHealth = 100.f;
	health = 100.f;

	defaultMaxMana = 100.f;
	maxMana = 100.f;
	mana = 100.f;

	defaultManaReg = 1.f;
	manaReg = 1.f;

	defaultArmour = 0.f;
	armour = 0.f;

	defaultFrostRes = 0.f;
	frostResistance = 0.f;

	defaultFireRes = 0.f;
	fireResistance = 0.f;

	defaultShockRes = 0.f;
	shockResistance = 0.f;

	defaultPoisonRes = 0.f;
	poisonResistance = 0.f;

	defaultDamageMultiplier = 1.f;
	damageMultiplier = 1.f;

	/* MOVEMENT STATS */
	defaultRotationRate = 640.f;
	rotationRate = 640.f;

	defaultMovementSpeed = 640.f;
	movementSpeed = 640.f;
}


// Called when the game starts
void UCharacterStatsComponent::InitializeComponent()
{
	Super::InitializeComponent();

	// ...
	
}


// Called every frame
void UCharacterStatsComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Stats component should never tick
}

