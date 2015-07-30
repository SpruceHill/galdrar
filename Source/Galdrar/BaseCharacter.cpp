// Fill out your copyright notice in the Description page of Project Settings.

#include "Galdrar.h"
#include "BaseCharacter.h"
#include "HUDAdapter.h"
#include "GaldrarColor.h"


void ABaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	GetCharacterMovement()->MaxWalkSpeed = stats->movementSpeed;
	GetCharacterMovement()->RotationRate = FRotator(0.f, stats->rotationRate, 0.f);

	// Mana regen
	if (stats->mana < stats->maxMana) stats->mana += stats->manaReg*DeltaSeconds;

	// Tick effects
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
				HA.CreateDamageIndicator(this, effect->GetPrint(), UGaldrarColor::GetDamageTypeColor(effect->GetDamageType()), false);
			}
		}
		if (effect->GetElapsedTime() >= effect->GetDuration())
		{
			it = activeEffects.erase(it);
		}
		++it;
	}

	// Tick spells
	for (Spell* s : spells)
	{
		if (s) s->Tick(DeltaSeconds);
	}

	// Tick stun
	if (bStunned)
	{
		stunTime += DeltaSeconds;
		if (stunTime >= stunDuration)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, name + " is no longer stunned");
			bStunned = false;
			stunTime = 0.f;
			stunDuration = 0.f;
		}
	}
}

void ABaseCharacter::Heal(float amount)
{
	HUDAdapter HA;
	HA.CreateDamageIndicator(this, "+"+FString::FromInt(amount), UGaldrarColor::GetHealColor(), false);
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
	HA.CreateDamageIndicator(this, FString::FromInt(amount), UGaldrarColor::GetDamageTypeColor(type), crit);

	stats->health -= amount;
	if (stats->health <= 0 && stats->health + amount > 0)
	{
		DisableInput(Cast<APlayerController>(GetController()));
		OnDeath();
		SetActorEnableCollision(false);
		SetActorHiddenInGame(true);
	}

	// Remove damage sensitive effects
	for (Effect* e : activeEffects)
	{
		if (e->bRemoveOnDamageTaken) e->End();
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

void ABaseCharacter::Stun(float duration)
{
	if (!bStunned)
	{
		HUDAdapter HA;
		HA.CreateDamageIndicator(this, "Stunned", FColor::White, false);
	}
	// Extend stun time if new stun is applied
	if (stunDuration - stunTime < duration)
	{
		stunDuration = stunTime + duration;
		bStunned = true;
	}
}

void ABaseCharacter::Silence(float duration)
{
	if (!bSilenced)
	{
		HUDAdapter HA;
		HA.CreateDamageIndicator(this, "Silenced", FColor::White, false);
	}
	// Extend silence time if new silence is applied
	if (silenceDuration - silenceTime < duration)
	{
		silenceDuration = silenceTime + duration;
		bSilenced = true;
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

/*
*	Effect Getters
*/
TArray<int32> ABaseCharacter::GetEffectIDs()
{
	TArray<int32> array;
	for (Effect* e : activeEffects)
	{
		array.Add(e->GetID());
	}

	return array;
}

TArray<float> ABaseCharacter::GetEffectDurations()
{
	TArray<float> array;
	for (Effect* e : activeEffects)
	{
		array.Add(e->GetDuration());
	}

	return array;
}

TArray<float> ABaseCharacter::GetEffectElapsedTimes()
{
	TArray<float> array;
	for (Effect* e : activeEffects)
	{
		array.Add(e->GetElapsedTime());
	}

	return array;
}

bool ABaseCharacter::IsStunned()
{
	return bStunned;
}

bool ABaseCharacter::IsSilenced()
{
	return bSilenced;
}
