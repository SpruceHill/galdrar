// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "BaseHealthPotion.h"

void ABaseHealthPotion::Activate(UCharacterStatsComponent* ownerStats, UCharacterStatsComponent* targetStats)
{
	targetStats->health += 2.f;
}


