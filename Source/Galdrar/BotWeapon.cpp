// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "BotWeapon.h"

UBotWeapon::UBotWeapon()
{
	name = "Uninitiated Bot Weapon";
	damage = 20.f;
	damageType = EGaldrarDamageType::FROST;
	critMultiplier = 1.5f;
	range = 140.f;
	attackSpeed = 1.f;
	cooldown = 1.f;
	bDoesDamage = true;

	weight = 20.f;
	kills = 0;
	twoHanded = false;

	// 1 = Weapon, ID 0001
	ID = 19999;

	animationAttackDelay.Add(0.3f);
	animationAttackDelay.Add(0.2f);
	animationAttackDelay.Add(0.2f);
	animationAttackDelay.Add(0.3f);
}


