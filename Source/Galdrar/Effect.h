// Copyright Spruce Hill, All rights reserved.

#pragma once
#include "GaldrarDamageType.h"
#include "CharacterStatsComponent.h"
#include "EffectType.h"
/**
 * 
 */
class GALDRAR_API Effect
{
public:
	Effect();
	Effect(UCharacterStatsComponent* stats);
	virtual void Tick(float delta);

	float GetDamage() { return damage; }

	float GetTime() { return time; }
	float GetDuration() { return duration; }
	float GetElapsedTime() { return elapsedTime; }

	EGaldrarDamageType GetDamageType() { return damageType; }
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
	EGaldrarDamageType damageType;
	UCharacterStatsComponent* stats;

};
