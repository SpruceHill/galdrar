// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "ManaRegenEffect.h"

ManaRegenEffect::ManaRegenEffect()
{
	// Sould not be called
}

ManaRegenEffect::ManaRegenEffect(CharacterStats* stats)
{
	this->stats = stats;
	name = "Mana Regeneration";
	desc = "+3 mana regeneration";
	damage = 3.f;
	duration = 10.f;
	timeLeft = 10.f;
	tickRate = 1.f;
	damageType = DamageType::PHYSICAL;
	time = 0.f;
	bStackable = false;
	effectType = EffectType::MANA_REGEN;
	bShouldTick = true;
	bPrintDI = false;
	doDamage = false;
	toBePrinted = "+" + FString::FromInt(damage);

	// 4 = Effect, ID = 0004
	ID = 40004;
}

void ManaRegenEffect::Tick(float delta)
{
	if (time == 0.f)
	{
		stats->manaReg += damage;
	}
	time += delta;
	if (time > tickRate)
	{
		timeLeft -= tickRate;
		time -= tickRate;
	}
	// Remove effect
	if (timeLeft <= 0.f)
	{
		stats->manaReg -= damage;
	}
}

ManaRegenEffect::~ManaRegenEffect()
{
}
