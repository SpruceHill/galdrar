// Copyright Spruce Hill, All rights reserved.

#pragma once
#include "DamageType.h"
/**
 * 
 */

class GALDRAR_API Effect
{
public:
	Effect();
	~Effect();
	virtual	void Affect(long delta);

protected:
	UPROPERTY(BlueprintReadOnly, Category = effect)
	float timeLeft;
	UPROPERTY(BlueprintReadOnly, Category = effect)
	float duration;
	UPROPERTY(BlueprintReadOnly, Category = effect)
	FString name;
	UPROPERTY(BlueprintReadOnly, Category = effect)
	FString desc;
	UDamageType damageType;
};
