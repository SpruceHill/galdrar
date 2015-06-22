// Fill out your copyright notice in the Description page of Project Settings.

#include "Galdrar.h"
#include "BaseCharacter.h"
#include "HUDAdapter.h"
#include "GaldrarColor.h"

void ABaseCharacter::Tick(float DeltaSeconds)
{
	 Super::Tick(DeltaSeconds);
	 if (stats->health <= 0)
	 {
		 GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, name + " just died");
		 this->Destroy();
	 }
	 for (Effect* effect : activeEffects)
	 {
		 if (effect->Tick(DeltaSeconds))
		 {
			 HUDAdapter HA;
			 HA.CreateDamageIndicator(this, effect->GetDamage(), GaldrarColor::GetDamageTypeColor(effect->GetType()), false);
			 Wound(effect->GetDamage());
		 }
	 }
}



void ABaseCharacter::Heal(float amount)
{
	stats->health += amount;
}

void ABaseCharacter::Wound(float amount)
{
	stats->health -= amount;
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
