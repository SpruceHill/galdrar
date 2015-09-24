// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "AttackComponent.h"
#include "BaseWeapon.generated.h"

/**
 * 
 */
UCLASS()
class GALDRAR_API UBaseWeapon : public UAttackComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = Weapon)
	float GetWeight();
	UFUNCTION(BlueprintCallable, Category = Weapon)
	int32 GetKills();
	UFUNCTION(BlueprintCallable, Category = Weapon)
	bool IsTwoHanded();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	float weight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	int32 kills;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	bool twoHanded;
};
