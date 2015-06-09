// Copyright Spruce Hill, All rights reserved.

#pragma once
#include "DamageType.h"
#include <list>
#include "Effect.h"

/**
 * An attack is a data container including all data needed to calculate damage and add effects.
 */
class GALDRAR_API Attack
{
public:
	Attack(float damage, DamageType type, float critPercentage);
	//, std::list < Effect* > effects
	float GetDamage(){ return damage; }
	DamageType GetAttackType(){ return attackType; }
	float GetCritPercent(){ return critPercentage; }
	std::list < Effect* > GetEffects(){ return effects; }
private:
	float damage;
	DamageType attackType;
	float critPercentage;
	std::list < Effect* > effects;
};
