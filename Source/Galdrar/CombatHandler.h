// Copyright Spruce Hill, All rights reserved.

#pragma once
#include "BaseCharacter.h"
#include "Attack.h"

/**
 * 
 */
class GALDRAR_API CombatHandler
{
public:
	UFUNCTION(BlueprintCallable, Category = Combat)
	static float AttackEnemy(ABaseCharacter* attacker, ABaseCharacter* defender, Attack* attack);
	static bool IsCritical(FVector attackerForward, FVector defenderForward);
private:
	// Degrees behind the player which will allow for backstabs (times 2)
	static const uint8 backStabDegree = 45;
	static float CalcDamage(float damage, float resistance, float critPercentage, bool crit);
};
