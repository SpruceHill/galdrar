// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "GasCloud.h"

GasCloud::GasCloud()
{
	activation = Activation::TARGET_GROUND;
	spellTarget = SpellTarget::CIRCLE;
	manaCost = 20.f;
	radius = 300.f;

	damage = 0.f;
	cooldown = 5.f;
	time = 5.f;
	effectTypes.push_back(EffectType::POISON_MILD);
	damageType = DamageType::POISON;
	range = 600.f;
}

GasCloud::~GasCloud()
{
}
