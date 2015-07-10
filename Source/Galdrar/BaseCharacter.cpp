// Fill out your copyright notice in the Description page of Project Settings.

#include "Galdrar.h"
#include "BaseCharacter.h"
#include "HUDAdapter.h"
#include "GaldrarColor.h"

void ABaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	std::list<Effect*>::iterator it = activeEffects.begin();
	while (it != activeEffects.end())
	{
		Effect* effect = (*it);

		if (effect->bShouldTick)
		{
			effect->Tick(DeltaSeconds);
			if (effect->bPrintDI)
			{
				HUDAdapter HA;
				HA.CreateDamageIndicator(this, FString::FromInt((int32)effect->GetDamage()), GaldrarColor::GetDamageTypeColor(effect->GetDamageType()), false);
				Wound(effect->GetDamage());
				effect->bPrintDI = false;
			}
		}
		if (effect->GetTimeLeft() <= 0.f)
		{
			it = activeEffects.erase(it);
		}
		++it;
	}
}

void ABaseCharacter::Heal(float amount)
{
	stats->health += amount;
}

void ABaseCharacter::Wound(float amount)
{
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

void ABaseCharacter::InitStats(float health, float armour, float frostRes, float fireRes, float shockRes, float dmgMultiplier, float rotRate, float movementSpeed)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "MaxHealth was: " + FString::SanitizeFloat(stats->maxHealth));
	if (health != 0.f)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Setting maxhealth to: " + FString::SanitizeFloat(health));
		stats->defaultMaxHealth = health;
		stats->maxHealth = health;
		stats->health = health;
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
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Maxhealth is now: " + FString::SanitizeFloat(stats->maxHealth));
}

float ABaseCharacter::GetHealth()
{
	return stats->health;
}

float ABaseCharacter::GetMaxHealth()
{
	return stats->maxHealth;
}
