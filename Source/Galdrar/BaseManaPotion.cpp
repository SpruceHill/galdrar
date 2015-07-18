// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "BaseManaPotion.h"

void ABaseManaPotion::Activate(CharacterStats* ownerStats, CharacterStats* targetStats)
{
	targetStats->manaReg += 2.f;
}


