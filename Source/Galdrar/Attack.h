// Copyright Spruce Hill, All rights reserved.

#pragma once
#include "DamageType.h"
#include <list>
#include "Effect.h"
#include "EffectType.h"

/**
 * An attack is a data container including all data needed to calculate damage and add effects.
 */
class GALDRAR_API Attack
{
public:
	Attack(FString name, float damage, DamageType type, float critMultiplier, float range, float attackSpeed, const std::list < EffectType > effectTypes);
	float GetDamage(){ return damage; }
	DamageType GetDamageType(){ return damageType; }
	float GetCritMultiplier(){ return critMultiplier; }
	std::list < EffectType > GetEffectTypes(){ return effectTypes; }
	float GetRange(){ return range; }
	float GetAttackSpeed(){ return attackSpeed; }
	FString GetName(){ return name; }
	bool isOnCoolDown(){ return onCooldown; }
	void setOnCoolDown(bool b) { onCooldown = b; }
private:
	float damage;
	DamageType damageType;
	float critMultiplier;
	std::list < EffectType > effectTypes;
	float range;
	float attackSpeed;
	FString name;
	bool onCooldown;
};
