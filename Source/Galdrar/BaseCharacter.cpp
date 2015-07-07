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

float ABaseCharacter::GetHealth()
{
	return stats->health;
}

float ABaseCharacter::GetMaxHealth()
{
	return stats->maxHealth;
}
