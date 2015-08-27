// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "CombatFunctionLibrary.h"
#include "GaldrarColor.h"
#include "EffectFunctionLibrary.h"


float UCombatFunctionLibrary::CalcDamage(float damage, float resistance, float critPercentage, bool crit)
{
	float calculatedDamage = damage;

	if (crit) calculatedDamage *= critPercentage;

	calculatedDamage *= 1 - (resistance / 100.f);

	return calculatedDamage;
}

void UCombatFunctionLibrary::AttackEnemy(ABaseCharacter* attacker, ABaseCharacter* defender, UAttackComponent* attack)
{
	if (attack->DoesDamage())
	{
		bool crit = false;
		if (attack->GetCritMultiplier() > 1.f) crit = IsCritical(attacker->GetActorForwardVector(), defender->GetActorForwardVector());

		float damage = CalcDamage(attacker->GetStats()->damageMultiplier * attack->GetDamage(), defender->GetResistance(attack->GetDamageType()),
			attack->GetCritMultiplier(), crit);

		defender->Wound((int32)damage, attack->GetDamageType(), crit);
	}
	for (int i = 0; i < attack->GetEffectTypes().Num(); i++)
	{
		ABaseCharacter* character = (UEffectFunctionLibrary::IsDefensive(attack->GetEffectTypes()[i]) ? attacker : defender);
		if (character->GetHealth() > 0)
			character->AddEffect(attack->GetEffectTypes()[i]);
	}
}

bool UCombatFunctionLibrary::IsCritical(FVector attackerForward, FVector defenderForward)
{
	return FVector::DotProduct(attackerForward, defenderForward) > FMath::Cos(FMath::DegreesToRadians(backStabDegree));
}



