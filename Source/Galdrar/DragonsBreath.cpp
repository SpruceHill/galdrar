// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "DragonsBreath.h"

DragonsBreath::DragonsBreath()
{
	activation = Activation::TARGET_GROUND;
	spellTarget = SpellTarget::CONE;
	float damage = 20.f;
	float manaCost = 40.f;
	float cooldown = 5.f;
	float time = 5.f;
	effectTypes.push_back(EffectType::BURNING);
	damageType = DamageType::FIRE;
	range = 600.f;
	radius = 200.f;
}

DragonsBreath::~DragonsBreath()
{
}
