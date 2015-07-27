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

	float GetTime() { return time; }
	//float GetTimeLeft() { return timeLeft; }
	float GetDuration() { return duration; }
	float GetElapsedTime() { return elapsedTime; }

	DamageType GetDamageType() { return damageType; }
	EffectType GetEffectType() { return effectType; }

	int32 GetID(){ return ID; }

	void ResetTimer()
	{
		elapsedTime = 0.f;
	}

	void End()
	{
		elapsedTime = duration;
	}

	FString GetPrint(){ bPrintDI = false; return toBePrinted; }

	bool bStackable;
	EffectType effectType;
	bool doDamage;
	bool bShouldTick;
	bool bPrintDI;
	bool bRemoveOnDamageTaken;

protected:
	float duration;
	float tickRate;

	float time;
	float elapsedTime;

	float damage;
	int32 ID;
	FString name;
	FString desc;
	FString toBePrinted;
	DamageType damageType;
	CharacterStats* stats;

};
