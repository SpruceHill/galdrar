// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "LightningBolt.h"

LightningBolt::LightningBolt()
{
	name = "Lighning Bolt";
	spellType = SpellType::LIGHNING_BOLT;
	activation = Activation::TARGET_GROUND;
	spellTarget = SpellTarget::CONE;
	manaCost = 40.f;
	radius = 50.f;
	bProjectile = true;
	bDoesDamage = true;

	damage = 10.f;
	cooldown = 5.f;
	time = 0.f;
	damageType = EGaldrarDamageType::SHOCK;
	range = 400.f;

	// 2 = Spell, ID = 0005
	ID = 20005;
}

LightningBolt::~LightningBolt()
{
}
