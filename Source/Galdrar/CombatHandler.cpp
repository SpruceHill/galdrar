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

float CombatHandler::AttackEnemy(ABaseCharacter* attacker, ABaseCharacter* defender, Attack* attack)
{
	FVector attackerLookAt = attacker->GetActorForwardVector();
	FVector defenderLookAt = defender->GetActorForwardVector();
	bool crit = FVector::DotProduct(attackerLookAt, defenderLookAt) > FMath::Cos(FMath::DegreesToRadians(backStabDegree));
	if (crit)GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, "CRIT");

	float damage = CalcDamage(attacker->GetDamage(), defender->GetResistance(attack->GetAttackType()),
		attack->GetCritMultiplier(), crit);

	//UGameplayStatics::ApplyDamage(defender, damage, NULL, attacker, UDamageType::StaticClass());
	return damage;

	//for(Effect* effect : attack->GetEffects())
	//{ 
	//	defender.addEffect(effect);
	//}
}

