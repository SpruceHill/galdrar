 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DamageType.h"
#include <list>
#include <algorithm>
#include "Effect.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"


UCLASS(abstract)
class GALDRAR_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Called every frame
	virtual void Tick(float DeltaSeconds) override { Super::Tick(DeltaSeconds); }

	float GetDamage() { return damage; }
	float GetResistance(DamageType type) 
	{
		switch (type) {
		case DamageType::PHYSICAL: return armour;
		case DamageType::FROST: return frostResistance;
		case DamageType::FIRE: return fireResistance;
		case DamageType::SHOCK: return shockResistance;
		case DamageType::TRUE: return 1.f;
		default: return 1.f;
		}
	}
	void heal(float amount)
	{
		health += amount;
	}
	void wound(float amount)
	{
		health -= amount;
	}
	void setHealth(float newHealth)
	{
		health = newHealth;
	}
	void addEffect(Effect* effect)
	{
		activeEffects.push_back(effect);
	}
	void removeEffect(Effect* effect)
	{
		bool found = (std::find(activeEffects.begin(), activeEffects.end(), effect) != activeEffects.end());
		if (found) activeEffects.remove(effect);
	}
protected:
	UPROPERTY(BlueprintReadOnly, Category = character)
	float maxHealth;
	UPROPERTY(BlueprintReadOnly, Category = character)
	float health;
	UPROPERTY(BlueprintReadOnly, Category = character)
	FString name;
	UPROPERTY(BlueprintReadOnly, Category = character)
	float damage;
	UPROPERTY(BlueprintReadOnly, Category = character)
	float armour;
	UPROPERTY(BlueprintReadOnly, Category = character)
	float frostResistance;
	UPROPERTY(BlueprintReadOnly, Category = character)
	float fireResistance;
	UPROPERTY(BlueprintReadOnly, Category = character)
	float shockResistance;
	std::list < Effect* > activeEffects;
	// Array / variables spells
};