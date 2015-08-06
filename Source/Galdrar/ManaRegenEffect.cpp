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
	elapsedTime = 0.f;
	
	damageType = EGaldrarDamageType::PHYSICAL;
	bStackable = false;
	effectType = EffectType::MANA_REGEN;
	bShouldTick = true;
	bPrintDI = false;
	doDamage = false;
	toBePrinted = "+" + FString::FromInt(damage);
	bRemoveOnDamageTaken = true;

	// 4 = Effect, ID = 0004
	ID = 40004;

	// Apply effect
	stats->manaReg += damage;
}

void ManaRegenEffect::Tick(float delta)
{
	elapsedTime += delta;

	// Remove effect
	if (elapsedTime >= duration || stats->mana >= stats->maxMana)
	{
		stats->manaReg -= damage;
		elapsedTime = duration;
	}
}

ManaRegenEffect::~ManaRegenEffect()
{
}
