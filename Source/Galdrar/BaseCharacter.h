 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DamageType.h"
#include "Attack.h"
#include <list>
#include <algorithm>
#include "Effect.h"
#include "CharacterStats.h"
#include "Spell.h"
#include "DamageType.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"


UCLASS(abstract)
class GALDRAR_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Called every frame

	virtual void Tick(float DeltaSeconds) override;

	FString GetName() { return name; }

	float GetDamage() { return weapon->GetDamage(); }

	Attack* GetWeapon() { return weapon; }

	CharacterStats* GetStats() { return stats; }

	float GetResistance(DamageType type)
	{
		switch (type) {
		case DamageType::PHYSICAL: return stats->armour;
		case DamageType::FROST: return stats->frostResistance;
		case DamageType::FIRE: return stats->fireResistance;
		case DamageType::SHOCK: return stats->shockResistance;
		case DamageType::POISON: return stats->poisonResistance;
		case DamageType::TRUE: return 0.f;
		default: return 0.f;
		}
		return 0.f;
	}

	UFUNCTION(BlueprintCallable, Category = Stats)
	void Heal(float amount);

	void Wound(float amount, DamageType type, bool crit);

	UFUNCTION(BlueprintCallable, Category = Stats)
	void SetHealth(float newHealth);

	UFUNCTION(BlueprintCallable, Category = Stats)
	void InitStats(float health, float armour, float frostRes, float fireRes, float shockRes, float poisonRes, float dmgMultiplier, float rotRate, float movementSpeed);

	void AddEffect(Effect* effect)
	{
		activeEffects.push_back(effect);
	}

	void RemoveEffect(Effect* effect)
	{
		bool found = (std::find(activeEffects.begin(), activeEffects.end(), effect) != activeEffects.end());
		if (found) activeEffects.remove(effect);
	}

	std::list < Effect* > GetActiveEffects() { return activeEffects; }

	Spell* GetSpell(int8 index)
	{
		return spells[index];
	}

	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override
	{
		//Wound(DamageAmount);
		return DamageAmount;
	}

	UFUNCTION(BlueprintCallable, Category = Stat)
	float GetHealth();
	UFUNCTION(BlueprintCallable, Category = Stat)
	float GetMaxHealth();
protected:
	CharacterStats* stats;
	UPROPERTY(BlueprintReadWrite, Category = character)
	FString name;
	std::list < Effect* > activeEffects;
	Attack* weapon;
	Spell* spells [4];
};
