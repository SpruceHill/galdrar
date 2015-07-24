// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "CommonBloodVial.h"

CommonBloodVial::CommonBloodVial(){ /* Do not call */ }

CommonBloodVial::CommonBloodVial(CharacterStats* stats)
{
	this->stats = stats;

	// 5 = Blood Vial, 0001 = ID
	ID = 50001;

	maxCharges = 100;
	charges = 40;
	cost = 20;
}

void CommonBloodVial::Activate()
{
	if (charges >= cost)
	{
		charges -= cost;
		if (stats->health + cost >= stats->maxHealth)
		{
			stats->health = stats->maxHealth;
		}
		else
		{
			stats->health += cost;
		}
	}
}


CommonBloodVial::~CommonBloodVial()
{
}
