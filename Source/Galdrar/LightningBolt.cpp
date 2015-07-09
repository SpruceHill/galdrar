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
	time = 5.f;
	damageType = DamageType::SHOCK;
	range = 400.f;
}

LightningBolt::~LightningBolt()
{
}
