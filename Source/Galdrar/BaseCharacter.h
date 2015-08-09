 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GaldrarDamageType.h"
#include "Attack.h"
#include <list>
#include <algorithm>
#include "Effect.h"
#include "CharacterStatsComponent.h"
#include "Spell.h"
#include "BaseEffectComponent.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class GALDRAR_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;

	FString GetName() { return name; }

	float GetDamage() { return weapon->GetDamage(); }

	Attack* GetWeapon() { return weapon; }

	UCharacterStatsComponent* GetStats() { return stats; }

	float GetResistance(EGaldrarDamageType type)
	{
		switch (type) {
		case EGaldrarDamageType::PHYSICAL: return stats->armour;
		case EGaldrarDamageType::FROST: return stats->frostResistance;
		case EGaldrarDamageType::FIRE: return stats->fireResistance;
		case EGaldrarDamageType::SHOCK: return stats->shockResistance;
		case EGaldrarDamageType::POISON: return stats->poisonResistance;
		default: return 0.f;
		}
		return 0.f;
	}

	UFUNCTION(BlueprintCallable, Category = Stats)
	void Heal(float amount);

	void Wound(float amount, EGaldrarDamageType type, bool crit);

	UFUNCTION(BlueprintCallable, Category = Stats)
	void SetHealth(float newHealth);

	UFUNCTION(BlueprintCallable, Category = Stats)
	void SetMana(float newMana);

	UFUNCTION(BlueprintCallable, Category = Stats)
	void DecreaseMana(float amount);

	void AddEffect(EffectType type)
	{
		bool found = false;
		for (Effect* e : activeEffects)
		{
			if (e->GetEffectType() == type)
			{
				found = true;
				if (e->bStackable)
				{
					// Effect stackable, add new instance.
					//activeEffects.push_back(EffectFactory::GenerateEffect(stats, type));
				}
				else
				{
					// Effect not stackable, reset timer.
					e->ResetTimer();
				}
			}
		}
		if (!found)
		{
			// Adding new effect.
			//activeEffects.push_back(EffectFactory::GenerateEffect(stats, type));
		}
	}

	void RemoveEffect(Effect* effect)
	{
		bool found = (std::find(activeEffects.begin(), activeEffects.end(), effect) != activeEffects.end());
		if (found) activeEffects.remove(effect);
	}

	std::list< Effect* > GetActiveEffects() { return activeEffects; }

	Spell* GetSpell(int8 index)
	{
		return spells[index];
	}

	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser) override
	{
		//Wound(DamageAmount);
		return DamageAmount;
	}

	UFUNCTION(BlueprintCallable, Category = BaseCharacter)
	void Stun(float duration);

	UFUNCTION(BlueprintCallable, Category = BaseCharacter)
	void Silence(float duration);

	UFUNCTION(BlueprintCallable, Category = Stat)
	float GetHealth();
	UFUNCTION(BlueprintCallable, Category = Stat)
	float GetMaxHealth();
	UFUNCTION(BlueprintCallable, Category = Stat)
	float GetMaxMana();
	UFUNCTION(BlueprintCallable, Category = Stat)
	float GetMana();

	/*
	*	SPELL GETTERS
	*/
	UFUNCTION(BlueprintCallable, Category = Spells)
	int32 GetSpellIdAtIndex(int32 index);

	UFUNCTION(BlueprintCallable, Category = Spells)
	float GetSpellCooldownAtIndex(int32 index);

	UFUNCTION(BlueprintCallable, Category = Spells)
	float GetSpellTimeAtIndex(int32 index);

	UFUNCTION(BlueprintCallable, Category = Spells)
	FString GetSpellNameAtIndex(int32 index);

	UFUNCTION(BlueprintCallable, Category = Spells)
	FString GetSpellDescAtIndex(int32 index);

	UFUNCTION(BlueprintCallable, Category = Spells)
	float GetSpellManaCostAtIndex(int32 index);

	UFUNCTION(BlueprintCallable, Category = Effects)
	TArray<int32> GetEffectIDs();
	UFUNCTION(BlueprintCallable, Category = Effects)
	TArray<float> GetEffectDurations();
	UFUNCTION(BlueprintCallable, Category = Effects)
	TArray<float> GetEffectElapsedTimes();

	UFUNCTION(BlueprintCallable, Category = BaseCharacter)
	bool IsStunned();

	UFUNCTION(BlueprintCallable, Category = BaseCharacter)
	bool IsSilenced();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = BaseCharacter)
	void OnDeath();

	UFUNCTION(BlueprintImplementableEvent, Category = BaseCharacter)
	void AttackAnimation();

	UFUNCTION(BlueprintCallable, Category = BaseCharacter)
	TArray<UActorComponent*> GetActiveEffectComponents();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = BaseCharacter, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CursorHitbox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BaseCharacter)
	UCharacterStatsComponent* stats;
	UPROPERTY(BlueprintReadWrite, Category = BaseCharacter)
	FString name;
	std::list < Effect* > activeEffects;
	Attack* weapon;
	Spell* spells [4];
	bool bStunned = false;
	bool bSilenced = false;

private:
	float stunTime = 0.f;
	float stunDuration = 0.f;

	float silenceTime = 0.f;
	float silenceDuration = 0.f;
};
