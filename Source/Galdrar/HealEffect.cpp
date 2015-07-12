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
	name = "Heal";
	desc = "A burst of life";
	damage = 5.f;
	duration = 2.f;
	timeLeft = 2.f;
	tickRate = 0.5f;
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
