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
	Attack(FString name, float damage, DamageType type, float critMultiplier, float range, float attackSpeed);
	//, std::list < Effect* > effects
	float GetDamage(){ return damage; }
	DamageType GetAttackType(){ return attackType; }
	float GetCritMultiplier(){ return critMultiplier; }
	std::list < Effect* > GetEffects(){ return effects; }
	float GetRange(){ return range; }
	float GetAttackSpeed(){ return attackSpeed; }
	FString GetName(){ return name; }
	bool isOnCoolDown(){ return onCooldown; }
	void setOnCoolDown(bool b) { onCooldown = b; }
private:
	float damage;
	DamageType attackType;
	float critMultiplier;
	std::list < Effect* > effects;
	float range;
	float attackSpeed;
	FString name;
	bool onCooldown;
};
