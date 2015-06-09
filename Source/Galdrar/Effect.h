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
	void Affect(long delta);

private:
	UPROPERTY(BlueprintReadOnly, Category = effect)
	float timeLeft;
	UPROPERTY(BlueprintReadOnly, Category = effect)
	float duration;
	UPROPERTY(BlueprintReadOnly, Category = effect)
	FString name;
	UPROPERTY(BlueprintReadOnly, Category = effect)
	FString desc;
	UPROPERTY(BlueprintReadOnly, Category = effect)
	DamageType damageType;
};
