// Copyright Spruce Hill, All rights reserved.

#pragma once

/**
 * 
 */
class GALDRAR_API CharacterStats
{
public:
	CharacterStats();
	~CharacterStats();

	/* COMBAT STATS */
	float defaultMaxHealth = 100.f;
	float maxHealth = 100.f;
	float health = 100.f;

	float defaultArmour = 1.f;
	float armour = 1.f;

	float defaultFrostRes = 1.f;
	float frostResistance = 1.f;

	float defaultFireRes = 1.f;
	float fireResistance = 1.f;

	float defaultShockRes = 1.f;
	float shockResistance = 1.f;

	float defaultDamageMultiplier = 1.f;
	float damageMultiplier = 1.f;

	/* MOVEMENT STATS */
	float defaultRotationRate = 640.f;
	float rotationRate = 640.f;

	float defaultMovementSpeed = 640.f;
	float movementSpeed = 640.f;
};
