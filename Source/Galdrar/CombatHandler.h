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
	static void AttackEnemy(ABaseCharacter* attacker, ABaseCharacter* defender, Attack* attack, bool crit);

private:
	static float CalcDamage(float damage, float resistance, float critPercentage, bool crit);
};
