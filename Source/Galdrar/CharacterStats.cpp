// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "CharacterStats.h"

CharacterStats::CharacterStats()
{
	/* COMBAT STATS */
	defaultMaxHealth = 100.f;
	maxHealth = 100.f;
	health = 100.f;

	defaultArmour = 1.f;
	armour = 1.f;

	defaultFrostRes = 1.f;
	frostResistance = 1.f;
	
	defaultFireRes = 1.f;
	fireResistance = 1.f;

	defaultShockRes = 1.f;
	shockResistance = 1.f;

	defaultPoisonRes = 1.f;
	poisonResistance = 1.f;

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
