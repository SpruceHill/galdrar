// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "HotHeaded.h"
#include "BaseCharacter.h"


UHotHeaded::UHotHeaded()
{
	name = "Hot Headed";
	desc = "Generate Rage twice as fast and lower rage degenerate rate by half.";

	traitActivation = ETraitActivation::Type::ON_CREATION;

	if (ABaseCharacter* character = dynamic_cast<ABaseCharacter*>(GetOwner()))
	{
		UCharacterStatsComponent* stats = character->GetStats();
		stats->rageGenerationMultiplier *= 2;
		stats->rageDegenerationRate *= 0.5f;
	}
}

