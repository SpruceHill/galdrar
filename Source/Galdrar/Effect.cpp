// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "Effect.h"
#include "CombatHandler.h"

Effect::Effect(CharacterStats* stats)
{
	this->stats = stats;
	damage = 5.f;
	duration = 5.f;
	timeLeft = 5.f;
	damageType = DamageType::FIRE;
	time = 0.f;
}
bool Effect::Tick(float delta)
{
	time += delta;
	if (time > 0.5f)
	{
		timeLeft -= 0.5f;
		//stats->health -= 20.f;
		time -= 0.5f;
		return true;
	}
	return false;
}
