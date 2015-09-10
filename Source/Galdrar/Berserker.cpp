// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "Berserker.h"


UBerserker::UBerserker()
{
	name = "Berserker";
	desc = "Generate 5 Rage on each strike with your weapon.";

	traitActivation = ETraitActivation::Type::ON_ATTACKING;

	owner = Cast<ABaseCharacter>(GetOwner());
}

void UBerserker::ActivateTrait()
{
	owner->GenerateRage(5);
}

