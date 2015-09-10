// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "AngerManagement.h"
#include "BaseCharacter.h"


UAngerManagement::UAngerManagement()
{
	name = "Anger Management";
	desc = "Generate half the amount of rage and degenerate rage twice as fast.";

	traitActivation = ETraitActivation::Type::ON_CREATION;

	if (ABaseCharacter* character = dynamic_cast<ABaseCharacter*>(GetOwner()))
	{
		UCharacterStatsComponent* stats = character->GetStats();
		stats->rageGenerationMultiplier *= 0.5;
		stats->rageDegenerationRate *= 2;
	}
}

