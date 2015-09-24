// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "BaseCharacter.h"
#include "CombatFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class GALDRAR_API UCombatFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Combat)
	static void AttackEnemy(ABaseCharacter* attacker, ABaseCharacter* defender, UAttackComponent* attack);
	UFUNCTION(BlueprintCallable, Category = Combat)
	static bool IsCritical(FVector attackerForward, FVector defenderForward);
	UFUNCTION(BlueprintCallable, Category = Combat)
	static float CalcDamage(float damage, float resistance, float critPercentage, bool crit);
private:
	// Degrees behind the player which will allow for backstabs (times 2)
	static const uint8 backStabDegree = 45;
};
