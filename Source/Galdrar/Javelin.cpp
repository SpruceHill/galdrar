// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "Javelin.h"

Javelin::Javelin()
{
	name = "Javelin";
	spellType = SpellType::JAVELIN;
	activation = Activation::TARGET_GROUND;
	spellTarget = SpellTarget::CONE;
	manaCost = 40.f;
	radius = 50.f;
	bProjectile = true;
	bDoesDamage = true;

	damage = 30.f;
	cooldown = 5.f;
	time = 0.f;
	damageType = DamageType::PHYSICAL;
	range = 1600.f;
}

Javelin::~Javelin()
{
}
