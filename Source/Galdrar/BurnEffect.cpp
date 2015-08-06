// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "BurnEffect.h"
#include "CharacterStats.h"

BurnEffect::BurnEffect()
{
	//Should not be called
}

BurnEffect::BurnEffect(CharacterStats* stats)
{
	this->stats = stats;
	name = "Burning";
	desc = "On fire";
	damage = 5.f;

	duration = 2.f;
	tickRate = 0.5f;
	time = 0.f;
	elapsedTime = 0.f;
	
	damageType = EGaldrarDamageType::FIRE;
	bStackable = false;
	effectType = EffectType::BURNING;
	bShouldTick = true;
	bPrintDI = false;
	doDamage = false;
	toBePrinted = desc;
	bRemoveOnDamageTaken = false;

	// 4 = Effect, ID = 0001
	ID = 40001;
}

void BurnEffect::Tick(float delta)
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
