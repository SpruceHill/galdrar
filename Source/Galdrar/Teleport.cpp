// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "Teleport.h"

Teleport::Teleport()
{
	name = "Teleport";
	spellType = SpellType::TELEPORT;
	activation = Activation::TARGET_GROUND;
	spellTarget = SpellTarget::CIRCLE;
	manaCost = 5.f;
	radius = 50.f;
	bProjectile = false;
	bDoesDamage = false;

	damage = 10.f;
	cooldown = 2.f;
	time = 0.f;
	damageType = EGaldrarDamageType::PHYSICAL;
	range = 600.f;

	// 2 = Spell, ID = 0006
	ID = 20006;
}

Teleport::~Teleport()
{
}
