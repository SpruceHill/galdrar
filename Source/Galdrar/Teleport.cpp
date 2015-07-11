// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "Teleport.h"

Teleport::Teleport()
{
	name = "Teleport";
	spellType = SpellType::TELEPORT;
	activation = Activation::TARGET_GROUND;
	spellTarget = SpellTarget::CIRCLE;
	manaCost = 40.f;
	radius = 50.f;
	bProjectile = false;
	bDoesDamage = false;

	damage = 10.f;
	cooldown = 5.f;
	time = 5.f;
	damageType = DamageType::TRUE;
	range = 600.f;
}

Teleport::~Teleport()
{
}
