// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "Heal.h"

Heal::Heal()
{
	name = "Heal";
	spellType = SpellType::HEAL;
	activation = Activation::TARGET_UNIT;
	spellTarget = SpellTarget::UNIT;
	manaCost = 40.f;
	radius = 50.f;
	bProjectile = false;
	bDoesDamage = false;

	damage = 10.f;
	cooldown = 5.f;
	time = 5.f;
	damageType = DamageType::PHYSICAL;
	range = 200.f;
}

Heal::~Heal()
{
}
