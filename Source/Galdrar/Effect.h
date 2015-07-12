// Copyright Spruce Hill, All rights reserved.

#pragma once
#include "DamageType.h"
#include "CharacterStats.h"
#include "EffectType.h"
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
	DamageType GetDamageType() { return damageType; }
	EffectType GetEffectType() { return effectType; }
	void ResetTimer() { timeLeft = duration; }
	FString GetPrint(){ bPrintDI = false; return toBePrinted; }

	bool bStackable;
	EffectType effectType;
	bool doDamage;
	bool bShouldTick;
	bool bPrintDI;

protected:
	float timeLeft;
	float duration;
	float tickRate;
	float time;
	float damage;
	FString name;
	FString desc;
	FString toBePrinted;
	DamageType damageType;
	CharacterStats* stats;
};
