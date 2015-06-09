// Copyright Spruce Hill, All rights reserved.

#pragma once

/**
 * 
 */
UCLASS(abstract)
class GALDRAR_API Effect
{
public:
	virtual void Affect(ABaseCharacter character, long delta);

private:
	UPROPERTY(BlueprintReadOnly, Category = effect)
	float timeLeft;
	UPROPERTY(BlueprintReadOnly, Category = character)
	float duration;
	UPROPERTY(BlueprintReadOnly, Category = character)
	FString name;
	UPROPERTY(BlueprintReadOnly, Category = character)
	FString desc;
	UPROPERTY(BlueprintReadOnly, Category = character)
	DamageType damageType;
};
