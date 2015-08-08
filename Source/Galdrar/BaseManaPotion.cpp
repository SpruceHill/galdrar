// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "BaseManaPotion.h"

void ABaseManaPotion::Activate(UCharacterStatsComponent* ownerStats, UCharacterStatsComponent* targetStats)
{
	targetStats->manaReg += 2.f;
}


