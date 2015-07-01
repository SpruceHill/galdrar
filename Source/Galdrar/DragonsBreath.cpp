// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "DragonsBreath.h"

DragonsBreath::DragonsBreath()
{
	activation = Activation::TARGET_GROUND;
	spellTarget = SpellTarget::CONE;
	manaCost = 40.f;
	radius = 200.f;

	damage = 20.f;
	cooldown = 5.f;
	time = 5.f;
	effectTypes.push_back(EffectType::BURNING);
	damageType = DamageType::FIRE;
	range = 600.f;
}

DragonsBreath::~DragonsBreath()
{
}
