// Copyright Spruce Hill, All rights reserved.

#pragma once
#include "DamageType.h"
#include "CharacterStats.h"
/**
 * 
 */
class GALDRAR_API Effect
{
public:
	Effect();
	Effect(CharacterStats* stats);
	~Effect();
	bool Tick(float delta);

	float GetDamage() { return damage; }
	DamageType GetType() { return damageType; }

protected:
	float timeLeft;
	float duration;
	float tickRate;
	float damage;
	FString name;
	FString desc;
	DamageType damageType;

private:
	CharacterStats* stats;
	float time;
	float oldTime;
};
