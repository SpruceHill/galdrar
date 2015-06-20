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
	Effect(CharacterStats* stats);
	~Effect();
	virtual	void Tick(float delta);

protected:
	UPROPERTY(BlueprintReadOnly, Category = Effect)
	float timeLeft;
	UPROPERTY(BlueprintReadOnly, Category = Effect)
	float duration;
	UPROPERTY(BlueprintReadOnly, Category = Effect)
	FString name;
	UPROPERTY(BlueprintReadOnly, Category = Effect)
	FString desc;
	DamageType damageType;

private:
	CharacterStats* stats;
	float time;
	float oldTime;
};
