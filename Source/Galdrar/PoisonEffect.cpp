// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "PoisonEffect.h"
#include "CharacterStats.h"

PoisonEffect::PoisonEffect()
{
	//Should not be called
}

PoisonEffect::PoisonEffect(CharacterStats* stats)
{
	this->stats = stats;
	name = "Poisoned";
	desc = "You are poisoned.";
	damage = 3.f;
	duration = 10.f;
	timeLeft = 10.f;
	tickRate = 1.f;
	damageType = DamageType::POISON;
	time = 0.f;
	bStackable = false;
	effectType = EffectType::POISON_MILD;
	bShouldTick = true;
	bPrintDI = false;
}

void PoisonEffect::Tick(float delta)
{
	time += delta;
	if (time > tickRate)
	{
		timeLeft -= tickRate;
		time -= tickRate;
		bPrintDI = true;
	}
	else
	{
		bPrintDI = false;
	}
}
