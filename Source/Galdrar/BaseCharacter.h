 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DamageType.h"
#include "Attack.h"
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
	virtual void Tick(float DeltaSeconds) override { 
		Super::Tick(DeltaSeconds); 
		if (health <= 0)
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
		case DamageType::PHYSICAL: return armour;
		case DamageType::FROST: return frostResistance;
		case DamageType::FIRE: return fireResistance;
		case DamageType::SHOCK: return shockResistance;
		case DamageType::TRUE: return 1.f;
		default: return 1.f;
		}
		return 1.f;
	}

	void Heal(float amount)
	{
		health += amount;
	}

	void Wound(float amount)
	{
		health -= amount;
	}

	void SetHealth(float newHealth)
	{
		health = newHealth;
	}

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
		//DamageEvent.DamageTypeClass;
		Wound(DamageAmount);
		return DamageAmount;
	}

protected:
	UPROPERTY(BlueprintReadOnly, Category = character)
	float maxHealth;
	UPROPERTY(BlueprintReadWrite, Category = character)
	float health;
	UPROPERTY(BlueprintReadOnly, Category = character)
	FString name;
	UPROPERTY(BlueprintReadOnly, Category = character)
	float armour;
	UPROPERTY(BlueprintReadOnly, Category = character)
	float frostResistance;
	UPROPERTY(BlueprintReadOnly, Category = character)
	float fireResistance;
	UPROPERTY(BlueprintReadOnly, Category = character)
	float shockResistance;

	std::list < Effect* > activeEffects;

	Attack* weapon;
	
	// Array / variables spells
};