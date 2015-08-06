// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "Heal.h"

HealSpell::HealSpell()
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
	time = 0.f;
	damageType = EGaldrarDamageType::PHYSICAL;
	range = 200.f;

	// 2 = Spell, ID = 0003
	ID = 20003;
}

HealSpell::~HealSpell()
{
}
