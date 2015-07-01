// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "Sword.h"

Sword::Sword()
{
	name = "Sword"; 
	damage = 20.f; 
	damageType = DamageType::PHYSICAL;
	critMultiplier = 1.5f;
	range = 100.f;
	attackSpeed = 1.f;
	cooldown = 1.f;

	weight = 1.f;
	kills = 0;
	twoHanded = false;
}

Sword::~Sword()
{
}
