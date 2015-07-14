// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "DragonsBreath.h"

DragonsBreath::DragonsBreath()
{
	name = "Dragon's Breath";
	spellType = SpellType::DRAGONS_BREATH;
	activation = Activation::TARGET_GROUND;
	spellTarget = SpellTarget::CONE;
	manaCost = 40.f;
	radius = 200.f;
	bProjectile = true;
	bDoesDamage = true;

	damage = 20.f;
	cooldown = 5.f;
	time = 0.f;
	effectTypes.push_back(EffectType::BURNING);
	damageType = DamageType::FIRE;
	range = 600.f;

	// 2 = Spell, ID = 0001
	ID = 20001;
}

DragonsBreath::~DragonsBreath()
{
}
