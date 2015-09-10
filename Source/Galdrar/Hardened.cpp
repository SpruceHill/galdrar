// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "Hardened.h"
#include "BaseCharacter.h"

UHardened::UHardened()
{
	name = "Hardened";
	desc = "All resistances increased by 20%.";

	traitActivation = ETraitActivation::Type::ON_CREATION;

	if (ABaseCharacter* character = dynamic_cast<ABaseCharacter*>(GetOwner()))
	{
		UCharacterStatsComponent* stats = character->GetStats();
		
		stats->defaultFrostRes = stats->defaultFrostRes + 20;
		stats->frostResistance = stats->defaultFrostRes;

		stats->defaultFireRes = stats->defaultFireRes + 20;
		stats->fireResistance = stats->defaultFireRes;

		stats->defaultShockRes = stats->defaultShockRes + 20;
		stats->shockResistance = stats->defaultShockRes;

		stats->defaultPoisonRes = stats->defaultPoisonRes + 20;
		stats->poisonResistance = stats->defaultPoisonRes;

		stats->defaultArmour = stats->defaultArmour + 20;
		stats->armour = stats->defaultArmour;
	}
}


