// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "CombatHandler.h"
#include "BaseCharacter.h"
#include "DamageType.h"
#include "GaldrarHUD.h"
#include "GaldrarColor.h"
#include "HUDAdapter.h"
#include "EffectFactory.h"

float CombatHandler::CalcDamage(float damage, float resistance, float critPercentage, bool crit)
{
	float calculatedDamage = damage;

	if (crit) calculatedDamage *= critPercentage;

	calculatedDamage *= resistance;

	return calculatedDamage;
}

void CombatHandler::AttackEnemy(ABaseCharacter* attacker, ABaseCharacter* defender, Attack* attack)
{
	/*if (attacker) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "attacker exists");
	else GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "ATTACKER ERROR");
	if (defender) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "defender exists");
	else GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "DEFENDER ERROR");
	if (attack) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "attack exists");
	else GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "ATTACK ERROR");*/
	
	float damage = CalcDamage(attacker->GetStats()->damageMultiplier * attack->GetDamage(), defender->GetResistance(attack->GetDamageType()),
		attack->GetCritMultiplier(), IsCritical(attacker->GetActorForwardVector(), defender->GetActorForwardVector()));

	HUDAdapter HA;
	HA.CreateDamageIndicator(defender, FString::FromInt((int32)damage), GaldrarColor::GetDamageTypeColor(attack->GetDamageType()), 
		IsCritical(attacker->GetActorForwardVector(), defender->GetActorForwardVector()));

	defender->Wound(damage);

	for(EffectType effectType : attack->GetEffectTypes())
	{
		bool found = false;
		for (Effect* e : defender->GetActiveEffects())
		{
			if (e->GetEffectType() == effectType)
			{
				found = true;
				if (e->bStackable)
				{
					// Effect stackable, add new instance.
					defender->AddEffect(EffectFactory::GenerateEffect(defender->GetStats(), effectType));
				}
				else
				{
					// Effect not stackable, reset timer.
					e->ResetTimer();
				}
			}
		}
		if (!found)
		{
			// Adding new effect.
			defender->AddEffect(EffectFactory::GenerateEffect(defender->GetStats(), effectType));
		}
	}
}

bool CombatHandler::IsCritical(FVector attackerForward, FVector defenderForward)
{
	return FVector::DotProduct(attackerForward, defenderForward) > FMath::Cos(FMath::DegreesToRadians(backStabDegree));
}
