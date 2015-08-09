// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "GasCloud.h"
#include "GasCloudEffectComponent.h"

GasCloud::GasCloud()
{
	name = "Gas Cloud";
	spellType = SpellType::GAS_CLOUD;
	activation = Activation::TARGET_GROUND;
	spellTarget = SpellTarget::CIRCLE;
	manaCost = 20.f;
	radius = 300.f;
	bProjectile = false;
	bDoesDamage = false;

	damage = 0.f;
	cooldown = 5.f;
	time = 0.f;
	effectTypes.Add(UGasCloudEffectComponent::StaticClass());
	damageType = EGaldrarDamageType::POISON;
	range = 600.f;

	// 2 = Spell, ID = 0002
	ID = 20002;
}

GasCloud::~GasCloud()
{
}
