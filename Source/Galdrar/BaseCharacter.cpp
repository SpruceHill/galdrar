// Fill out your copyright notice in the Description page of Project Settings.

#include "Galdrar.h"
#include "BaseCharacter.h"
#include "HUDAdapter.h"
#include "GaldrarColor.h"


void ABaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	/*time += DeltaSeconds;
	if (time >= 1.f)
	{
		time = 0.f;
		if(stats->mana < stats->maxMana) stats->mana += stats->manaReg;
	}*/
	if (stats->mana < stats->maxMana) stats->mana += stats->manaReg*DeltaSeconds;

	std::list<Effect*>::iterator it = activeEffects.begin();
	while (it != activeEffects.end())
	{
		Effect* effect = (*it);

		if (effect->bShouldTick)
		{
			effect->Tick(DeltaSeconds);
			if (effect->doDamage)
			{
				float effectDamage = effect->GetDamage();
				effectDamage *= 1 - (GetResistance(effect->GetDamageType()) / 100.f);
				Wound((int32)effectDamage, effect->GetDamageType(), false);
				effect->bPrintDI = false;
			}
			if (effect->bPrintDI)
			{
				HUDAdapter HA;
				HA.CreateDamageIndicator(this, effect->GetPrint(), GaldrarColor::GetDamageTypeColor(effect->GetDamageType()), false);
			}
		}
		if (effect->GetTimeLeft() <= 0.f)
		{
			it = activeEffects.erase(it);
		}
		++it;
	}
/*	for (Effect* effect : activeEffects)
	{
		if (effect)
		{
			if (effect->bShouldTick)
			{
				effect->Tick(DeltaSeconds);
				if (effect->doDamage)
				{
					float effectDamage = effect->GetDamage();
					effectDamage *= 1 - (GetResistance(effect->GetDamageType()) / 100.f);
					Wound((int32)effectDamage, effect->GetDamageType(), false);
					effect->bPrintDI = false;
				}
				if (effect->bPrintDI)
				{
					HUDAdapter HA;
					HA.CreateDamageIndicator(this, effect->GetPrint(), GaldrarColor::GetDamageTypeColor(effect->GetDamageType()), false);
				}
			}
			if (effect->GetTimeLeft() <= 0.f)
			{
				activeEffects.Remove(effect);
			}
		}
	}*/

	for (Spell* s : spells)
	{
		if (s) s->Tick(DeltaSeconds);
	}
}

void ABaseCharacter::Heal(float amount)
{
	HUDAdapter HA;
	HA.CreateDamageIndicator(this, "+"+FString::FromInt(amount), GaldrarColor::GetHealColor(), false);
	if (stats->health + amount > stats->maxHealth)
	{
		stats->health = stats->maxHealth;
	}
	else
	{
		stats->health += amount;
	}
}

void ABaseCharacter::Wound(float amount, DamageType type, bool crit)
{
	HUDAdapter HA;
	HA.CreateDamageIndicator(this, FString::FromInt(amount), GaldrarColor::GetDamageTypeColor(type), crit);

	stats->health -= amount;
	if (stats->health <= 0 && stats->health + amount > 0)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, name + " just died");
	if (stats->health <= 0)
	{
		this->SetActorEnableCollision(false);
		this->SetActorHiddenInGame(true);
	}
}

void ABaseCharacter::SetHealth(float newHealth)
{
	stats->health = newHealth;
}

void ABaseCharacter::SetMana(float newMana)
{
	stats->mana = newMana;
}

void ABaseCharacter::DecreaseMana(float amount)
{
	if (stats->mana - amount <= 0.f) stats->mana = 0.f;
	else stats->mana -= amount;
}

void ABaseCharacter::InitStats(float health, float mana, float armour, float frostRes, float fireRes, float shockRes, float poisonRes, float dmgMultiplier, float rotRate, float movementSpeed)
{
	if (health != 0.f)
	{
		stats->defaultMaxHealth = health;
		stats->maxHealth = health;
		stats->health = health;
	}
	if (mana != 0.f)
	{
		stats->defaultMaxMana = mana;
		stats->maxMana = mana;
		stats->mana = mana;
	}
	if (armour != 0.f)
	{
		stats->defaultArmour = armour;
		stats->armour = armour;
	}
	if (frostRes != 0.f)
	{
		stats->defaultFrostRes = frostRes;
		stats->frostResistance = frostRes;
	}
	if (fireRes != 0.f)
	{
		stats->defaultFireRes = fireRes;
		stats->fireResistance = fireRes;
	}
	if (shockRes != 0.f)
	{
		stats->defaultShockRes = shockRes;
		stats->shockResistance = shockRes;
	}
	if (poisonRes != 0.f)
	{
		stats->defaultPoisonRes = poisonRes;
		stats->poisonResistance = poisonRes;
	}
	if (dmgMultiplier != 0.f)
	{
		stats->defaultDamageMultiplier = dmgMultiplier;
		stats->damageMultiplier = dmgMultiplier;
	}
	if (rotRate != 0.f)
	{
		stats->defaultRotationRate = rotRate;
		stats->rotationRate = rotRate;
		GetCharacterMovement()->RotationRate = FRotator(0.f, rotRate, 0.f);
	}
	if (movementSpeed != 0.f)
	{
		stats->defaultMovementSpeed = movementSpeed;
		stats->movementSpeed = movementSpeed;
		GetCharacterMovement()->MaxWalkSpeed = movementSpeed;
	}
}

float ABaseCharacter::GetHealth()
{
	return stats->health;
}

float ABaseCharacter::GetMaxHealth()
{
	return stats->maxHealth;
}

float ABaseCharacter::GetMaxMana()
{
	return stats->maxMana;
}

float ABaseCharacter::GetMana()
{
	return stats->mana;
}

TArray<int32> ABaseCharacter::GetEffectIDs()
{
	TArray<int32> array;
	for (Effect* e : activeEffects)
	{
		array.Add(e->GetID());
	}

	return array;
}
