// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "CharacterStats.h"

CharacterStats::CharacterStats()
{
	/* COMBAT STATS */
	defaultMaxHealth = 100.f;
	maxHealth = 100.f;
	health = 100.f;

	defaultArmour = 0.f;
	armour = 0.f;

	defaultFrostRes = 0.f;
	frostResistance = 0.f;
	
	defaultFireRes = 0.f;
	fireResistance = 0.f;

	defaultShockRes = 0.f;
	shockResistance = 0.f;

	defaultPoisonRes = 0.f;
	poisonResistance = 0.f;

	defaultDamageMultiplier = 1.f;
	damageMultiplier = 1.f;

	/* MOVEMENT STATS */
	defaultRotationRate = 640.f;
	rotationRate = 640.f;

	defaultMovementSpeed = 640.f;
	movementSpeed = 640.f;
}

CharacterStats::~CharacterStats()
{
}
