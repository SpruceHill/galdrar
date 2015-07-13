// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "HealEffect.h"

HealEffect::HealEffect()
{
	// Should not be called
}

HealEffect::HealEffect(CharacterStats* stats)
{
	this->stats = stats;
	name = "Regeneration";
	desc = "A burst of life";
	damage = 2.f;
	duration = 10.f;
	timeLeft = 10.f;
	tickRate = 1.f;
	damageType = DamageType::PHYSICAL;
	time = 0.f;
	bStackable = false;
	effectType = EffectType::HEAL;
	bShouldTick = true;
	bPrintDI = false;
	doDamage = false;
	toBePrinted = "+"+FString::FromInt(damage);
}

void HealEffect::Tick(float delta)
{
	time += delta;
	if (time > tickRate)
	{
		timeLeft -= tickRate;
		time -= tickRate;
		stats->health += damage;
		bPrintDI = true;
	}
	else
	{
		bPrintDI = false;
	}
}

HealEffect::~HealEffect()
{
}
