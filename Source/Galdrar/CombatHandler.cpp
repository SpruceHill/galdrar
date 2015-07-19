// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "CombatHandler.h"
#include "BaseCharacter.h"
#include "DamageType.h"
#include "GaldrarHUD.h"
#include "GaldrarColor.h"
#include "HUDAdapter.h"
#include "Weapon.h"
#include "EffectFactory.h"

float CombatHandler::CalcDamage(float damage, float resistance, float critPercentage, bool crit)
{
	float calculatedDamage = damage;

	if (crit) calculatedDamage *= critPercentage;

	calculatedDamage *= 1 - (resistance / 100.f);

	return calculatedDamage;
}

void CombatHandler::AttackEnemy(ABaseCharacter* attacker, ABaseCharacter* defender, Attack* attack)
{
	if (attack->DoesDamage())
	{
		bool crit = false;
		if (attack->GetCritMultiplier() > 1.f) crit = IsCritical(attacker->GetActorForwardVector(), defender->GetActorForwardVector());

		float damage = CalcDamage(attacker->GetStats()->damageMultiplier * attack->GetDamage(), defender->GetResistance(attack->GetDamageType()),
			attack->GetCritMultiplier(), crit);

		defender->Wound((int32)damage, attack->GetDamageType(), crit);
	}
	for(EffectType effectType : attack->GetEffectTypes())
	{
		ABaseCharacter* character = (EffectFactory::IsDefensive(effectType) ? attacker : defender);
		character->AddEffect(effectType);
	}
}

bool CombatHandler::IsCritical(FVector attackerForward, FVector defenderForward)
{
	return FVector::DotProduct(attackerForward, defenderForward) > FMath::Cos(FMath::DegreesToRadians(backStabDegree));
}
