// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "LightningBolt.h"

LightningBolt::LightningBolt()
{
	name = "Lighning Bolt";
	spellType = SpellType::LIGHNING_BOLT;
	activation = Activation::TARGET_UNIT;
	spellTarget = SpellTarget::UNIT;
	manaCost = 40.f;
	radius = 0.f;

	damage = 10.f;
	cooldown = 5.f;
	time = 5.f;
	//effectTypes.push_back(EffectType::BURNING);
	damageType = DamageType::SHOCK;
	range = 400.f;
}

LightningBolt::~LightningBolt()
{
}
