// Fill out your copyright notice in the Description page of Project Settings.

#include "Galdrar.h"
#include "BaseCharacter.h"

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
