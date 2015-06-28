// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "DragonsBreath.h"

DragonsBreath::DragonsBreath()
{
	spellType = SpellType::TARGET;
	float damage = 20.f;
	float manaCost = 40.f;
	float cooldown = 5.f;
	float time = 5.f;
	effectTypes.push_back(EffectType::BURNING);
	damageType = DamageType::FIRE;
	range = 600.f;
}

DragonsBreath::~DragonsBreath()
{
}
