// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "CombatHandler.h"
#include "DamageType.h"

void attack(ABaseCharacter* attacker, ABaseCharacter* defender, Attack* attack, bool crit)
{
	float damage = calcDamage(attacker->GetDamage(), defender->GetResistance(attack->GetAttackType()),
		attack->GetCritPercent(), crit);
}

float calcDamage(float damage, float resistance, float critPercent, bool crit)
{
	float calculatedDamage = damage;

	if (crit) calculatedDamage *= critPercent;
	
	calculatedDamage *= resistance;

	return calculatedDamage;
}
