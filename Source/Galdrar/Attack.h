// Copyright Spruce Hill, All rights reserved.

#pragma once
#include "GaldrarDamageType.h"
#include <list>
#include "Effect.h"
#include "EffectType.h"
#include "BaseEffectComponent.h"
#include "Runtime/Engine/Classes/Slate/SlateBrushAsset.h"

/**
 * An attack is a data container including all data needed to calculate damage and add effects.
 */
class GALDRAR_API Attack
{
public:
	Attack(FString name, float damage, EGaldrarDamageType type, float critMultiplier, float range, float attackSpeed, const TArray<TSubclassOf<UBaseEffectComponent>> effectTypes);
	
	float GetDamage(){ return damage; }
	EGaldrarDamageType GetDamageType(){ return damageType; }
	float GetCritMultiplier(){ return critMultiplier; }
	TArray<TSubclassOf<UBaseEffectComponent>> GetEffectTypes(){ return effectTypes; }
	float GetRange(){ return range; }
	float GetAttackSpeed(){ return attackSpeed; }
	virtual FString GetName(){ return name; }
	FString GetDesc(){ return desc; }
	
	bool IsProjectile(){ return bProjectile; }
	bool IsProjectilePenetrating(){ return bProjectilePenetration; }
	float GetProjectileWidth(){ return projectileWidth; }
	float GetProjectileSpeed(){ return projectileSpeed; }

	void Activate();
	void Tick(float deltaSeconds);
	bool IsOnCoolDown(){ return time > 0; }
	float GetTime(){ return time; }
	float GetCooldown(){ return cooldown; }

	bool DoesDamage(){ return bDoesDamage; }

	float GetID(){ return ID; }

	Attack();
	~Attack();
protected:
	bool bDoesDamage;
	float damage;
	EGaldrarDamageType damageType;
	float critMultiplier;
	TArray<TSubclassOf<UBaseEffectComponent>> effectTypes;
	float range;
	float attackSpeed;
	FString name;
	FString desc;

	float cooldown;
	float time;
	
	bool bProjectile;
	bool bProjectilePenetration;
	float projectileWidth;
	float projectileSpeed;

	float ID;
};
