// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "GasCloud.h"

GasCloud::GasCloud()
{
	name = "Gas Cloud";
	spellType = SpellType::GAS_CLOUD;
	activation = Activation::TARGET_GROUND;
	spellTarget = SpellTarget::CIRCLE;
	manaCost = 20.f;
	radius = 300.f;
	bProjectile = false;
	bDoesDamage = false;

	damage = 0.f;
	cooldown = 5.f;
	time = 0.f;
	effectTypes.push_back(EffectType::POISON_MILD);
	damageType = DamageType::POISON;
	range = 600.f;
}

GasCloud::~GasCloud()
{
}
