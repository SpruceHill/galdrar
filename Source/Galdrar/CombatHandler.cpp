// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "CombatHandler.h"
#include "BaseCharacter.h"
#include "DamageType.h"
#include "GaldrarHUD.h"
#include "GaldrarColor.h"
#include "HUDAdapter.h"

float CombatHandler::CalcDamage(float damage, float resistance, float critPercentage, bool crit)
{
	float calculatedDamage = damage;

	if (crit) calculatedDamage *= critPercentage;
	
	calculatedDamage *= resistance;

	return calculatedDamage;
}

void CombatHandler::AttackEnemy(ABaseCharacter* attacker, ABaseCharacter* defender, Attack* attack)
{
	float damage = CalcDamage(attacker->GetDamage(), defender->GetResistance(attack->GetDamageType()),
		attack->GetCritMultiplier(), IsCritical(attacker->GetActorForwardVector(), defender->GetActorForwardVector()));

	HUDAdapter HA;
	HA.CreateDamageIndicator(defender, FString::FromInt((int32)damage), GaldrarColor::GetDamageTypeColor(attack->GetDamageType()), 
		IsCritical(attacker->GetActorForwardVector(), defender->GetActorForwardVector()));

	defender->Wound(damage);

	//for(Effect* effect : attack->GetEffects())
	//{ 
	//	defender.addEffect(effect);
	//}
}

bool CombatHandler::IsCritical(FVector attackerForward, FVector defenderForward)
{
	return FVector::DotProduct(attackerForward, defenderForward) > FMath::Cos(FMath::DegreesToRadians(backStabDegree));
}


