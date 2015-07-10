// Copyright Spruce Hill, All rights reserved.

#pragma once

/**
 * This class contains all stats for a given BaseCharacter. All values are set in the 
 * constructor to the default values. Override in character class other values are needed.
 */
class GALDRAR_API CharacterStats
{
public:
	CharacterStats();
	~CharacterStats();

	/* COMBAT STATS */
	float defaultMaxHealth;
	float maxHealth;
	float health;

	float defaultArmour;
	float armour;

	float defaultFrostRes;
	float frostResistance;

	float defaultFireRes;
	float fireResistance;

	float defaultShockRes;
	float shockResistance;

	float defaultPoisonRes;
	float poisonResistance;

	float defaultDamageMultiplier;
	float damageMultiplier;

	/* MOVEMENT STATS */
	float defaultRotationRate;
	float rotationRate;

	float defaultMovementSpeed;
	float movementSpeed;
};
