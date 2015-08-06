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
	tickRate = 1.f;
	time = 0.f;
	elapsedTime = 0.f;
	
	damageType = EGaldrarDamageType::POISON;
	bStackable = false;
	effectType = EffectType::POISON_MILD;
	bShouldTick = true;
	bPrintDI = true;
	doDamage = false;
	toBePrinted = int32(damage * (1 - (stats->poisonResistance / 100.f))) > 0 ? name : "Immune";
	bRemoveOnDamageTaken = false;

	// 4 = Effect, ID = 0002
	ID = 40002;
}

void PoisonEffect::Tick(float delta)
{
	elapsedTime += delta;
	time += delta;
	if (time > tickRate)
	{
		time -= tickRate;
		doDamage = true;
	}
	else
	{
		doDamage = false;
	}
}
