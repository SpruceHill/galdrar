// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "DragonsBreath.h"
#include "BurnEffectComponent.h"

DragonsBreath::DragonsBreath()
{
	name = "Dragon's Breath";
	desc = "Shoot a ball of fire onto your enemies – damaging anyone in its path (20 fire damage) and sets them on fire.";
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
	effectTypes.Add(UBurnEffectComponent::StaticClass());
	damageType = EGaldrarDamageType::FIRE;
	range = 600.f;

	// 2 = Spell, ID = 0001
	ID = 20001;
}

DragonsBreath::~DragonsBreath()
{
}
