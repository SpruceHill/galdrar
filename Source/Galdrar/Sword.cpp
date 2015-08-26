// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "Sword.h"

USword::USword()
{
	name = "Sword";
	damage = 20.f;
	damageType = EGaldrarDamageType::PHYSICAL;
	critMultiplier = 1.5f;
	range = 100.f;
	attackSpeed = 1.f;
	cooldown = 1.f;
	bDoesDamage = true;

	weight = 1.f;
	kills = 0;
	twoHanded = false;

	// 1 = Weapon, ID 0001
	ID = 10001;
}


