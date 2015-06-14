// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "DamageType.h"
#include "CombatHandler.h"
#include "GaldrarHUD.h"

float CombatHandler::CalcDamage(float damage, float resistance, float critPercentage, bool crit)
{
	float calculatedDamage = damage;

	if (crit) calculatedDamage *= critPercentage;
	
	calculatedDamage *= resistance;

	return calculatedDamage;
}

float CombatHandler::AttackEnemy(ABaseCharacter* attacker, ABaseCharacter* defender, Attack* attack, bool crit)
{
	float damage = CalcDamage(attacker->GetDamage(), defender->GetResistance(attack->GetAttackType()),
		attack->GetCritPercent(), crit);

	defender->Wound(damage);
	return damage;

	//for(Effect* effect : attack->GetEffects())
	//{ 
	//	defender.addEffect(effect);
	//}
}

