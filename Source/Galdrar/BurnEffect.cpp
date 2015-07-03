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
	timeLeft = 2.f;
	tickRate = 0.5f;
	damageType = DamageType::FIRE;
	time = 0.f;
	bStackable = false;
	effectType = EffectType::BURNING;
	bShouldTick = true;
	bPrintDI = false;
}

void BurnEffect::Tick(float delta)
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
