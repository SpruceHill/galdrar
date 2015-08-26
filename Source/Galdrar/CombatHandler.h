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
	static void AttackEnemy(ABaseCharacter* attacker, ABaseCharacter* defender, UAttackComponent* attack);
	static bool IsCritical(FVector attackerForward, FVector defenderForward);
	static float CalcDamage(float damage, float resistance, float critPercentage, bool crit);
private:
	// Degrees behind the player which will allow for backstabs (times 2)
	static const uint8 backStabDegree = 45;
};
