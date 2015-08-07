// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "CommonBloodVial.h"

CommonBloodVial::CommonBloodVial(){ /* Do not call */ }

CommonBloodVial::CommonBloodVial(UCharacterStatsComponent* stats)
{
	this->stats = stats;

	// 5 = Blood Vial, 0001 = ID
	ID = 50001;

	maxCharges = 5;
	charges = 0;

	healAmount = 20;
}

void CommonBloodVial::Activate()
{
	if (stats->health < stats->maxHealth && charges >= 1)
	{
		charges -= 1;
		if (stats->health + healAmount >= stats->maxHealth)
		{
			stats->health = stats->maxHealth;
		}
		else
		{
			stats->health += healAmount;
		}
	}
}


CommonBloodVial::~CommonBloodVial()
{
}
