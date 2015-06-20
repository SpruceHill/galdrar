 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DamageType.h"
#include "Attack.h"
#include <list>
#include <algorithm>
#include "Effect.h"
#include "CharacterStats.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"


UCLASS(abstract)
class GALDRAR_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Called every frame
	virtual void Tick(float DeltaSeconds) override { 
		Super::Tick(DeltaSeconds); 
		if (stats->health <= 0)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, name + " just died");
			this->Destroy();
		}
	}

	FString GetName() { return name; }

	float GetDamage() {	return weapon->GetDamage(); }

	Attack* GetWeapon() { return weapon; }

	float GetResistance(DamageType type) 
	{
		switch (type) {
		case DamageType::PHYSICAL: return stats->armour;
		case DamageType::FROST: return stats->frostResistance;
		case DamageType::FIRE: return stats->fireResistance;
		case DamageType::SHOCK: return stats->shockResistance;
		case DamageType::TRUE: return 1.f;
		default: return 1.f;
		}
		return 1.f;
	}

	UFUNCTION(BlueprintCallable, Category = Stat)
	void Heal(float amount);

	UFUNCTION(BlueprintCallable, Category = Stat)
	void Wound(float amount);

	UFUNCTION(BlueprintCallable, Category = Stat)
	void SetHealth(float newHealth);

	void AddEffect(Effect* effect)
	{
		activeEffects.push_back(effect);
	}

	void RemoveEffect(Effect* effect)
	{
		bool found = (std::find(activeEffects.begin(), activeEffects.end(), effect) != activeEffects.end());
		if (found) activeEffects.remove(effect);
	}

	//UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Damage")
	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override
	{
		Wound(DamageAmount);
		return DamageAmount;
	}

	UFUNCTION(BlueprintCallable, Category = Stat)
	float GetHealth();
	UFUNCTION(BlueprintCallable, Category = Stat)
	float GetMaxHealth();
protected:
	CharacterStats* stats;
	UPROPERTY(BlueprintReadOnly, Category = character)
	FString name;
	/*UPROPERTY(BlueprintReadOnly, Category = character)
	float maxHealth;
	UPROPERTY(BlueprintReadWrite, Category = character)
	float health;
	UPROPERTY(BlueprintReadOnly, Category = character)
	float armour;
	UPROPERTY(BlueprintReadOnly, Category = character)
	float frostResistance;
	UPROPERTY(BlueprintReadOnly, Category = character)
	float fireResistance;
	UPROPERTY(BlueprintReadOnly, Category = character)
	float shockResistance;
	*/
	std::list < Effect* > activeEffects;

	Attack* weapon;
	
	// Array / variables spells
};