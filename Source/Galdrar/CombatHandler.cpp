// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "DamageType.h"
#include "CombatHandler.h"

float calcDamage(float damage, float resistance, float critPercentage, bool crit)
{
	float calculatedDamage = damage;

	if (crit) calculatedDamage *= critPercentage;
	
	calculatedDamage *= resistance;

	return calculatedDamage;
}

void attack(ABaseCharacter attacker, ABaseCharacter defender, Attack* attack, bool crit)
{
	float damage = calcDamage(attacker.GetDamage(), defender.GetResistance(attack->GetAttackType()),
		attack->GetCritPercent(), crit);

	defender.wound(damage);

	for(Effect* effect : attack->GetEffects())
	{ 
		defender.addEffect(effect);
	}
}

