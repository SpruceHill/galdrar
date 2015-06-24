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
	virtual void Tick(float delta);

	float GetDamage() { return damage; }
	float GetTimeLeft() { return timeLeft; }
	DamageType GetType() { return damageType; }

	bool bShouldTick;
	bool bPrintDI;

protected:
	float timeLeft;
	float duration;
	float tickRate;
	float damage;
	FString name;
	FString desc;
	DamageType damageType;
	CharacterStats* stats;
	float time;
};
