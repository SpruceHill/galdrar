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
	bool IsOnCoolDown(){ return currentCooldown > 0; }
	bool IsProjectile(){ return bProjectile; }
	bool IsProjectilePenetrating(){ return bProjectilePenetration; }
	float GetProjectileWidth(){ return projectileWidth; }
	float GetProjectileSpeed(){ return projectileSpeed; }
	float GetTime(){ return time; }

	Attack();
	~Attack();
protected:
	float damage;
	DamageType damageType;
	float critMultiplier;
	std::list < EffectType > effectTypes;
	float range;
	float attackSpeed;
	FString name;
	float cooldown;
	float currentCooldown;
	float time;
	
	bool bProjectile;
	bool bProjectilePenetration;
	float projectileWidth;
	float projectileSpeed;
};
