// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "HealEffect.h"

HealEffect::HealEffect()
{
	// Should not be called
}

HealEffect::HealEffect(UCharacterStatsComponent* stats)
{
	this->stats = stats;
	name = "Regeneration";
	desc = "A burst of life";
	damage = 2.f;

	duration = 10.f;
	tickRate = 1.f;
	time = 0.f;
	elapsedTime = 0.f;

	damageType = EGaldrarDamageType::PHYSICAL;
	bStackable = false;
	effectType = EffectType::HEAL;
	bShouldTick = true;
	bPrintDI = false;
	doDamage = false;
	toBePrinted = "+"+FString::FromInt(damage);
	bRemoveOnDamageTaken = true;

	// 4 = Effect, ID = 0003
	ID = 40003;
}

void HealEffect::Tick(float delta)
{
	elapsedTime += delta;
	time += delta;

	// Remove effect when fully healed
	if (stats->health >= stats->maxHealth)
	{
		stats->health = stats->maxHealth;
		elapsedTime = duration;
	}

	// Should tick
	if (time > tickRate)
	{
		//timeLeft -= tickRate;
		time -= tickRate;

		// Heal
		if (stats->health + damage >= stats->maxHealth)
		{
			stats->health = stats->maxHealth;
		}
		else
		{
			stats->health += damage;
		}

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
