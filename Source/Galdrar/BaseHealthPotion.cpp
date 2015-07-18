// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "BaseHealthPotion.h"

void ABaseHealthPotion::Activate(CharacterStats* ownerStats, CharacterStats* targetStats)
{
	targetStats->health += 2.f;
}


