 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GaldrarDamageType.h"
#include "Attack.h"
#include <list>
#include <algorithm>
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

	void Wound(int32 amount, EGaldrarDamageType type, bool crit);

	UFUNCTION(BlueprintCallable, Category = Stats)
	void SetHealth(float newHealth);

	UFUNCTION(BlueprintCallable, Category = Stats)
	void SetMana(float newMana);

	UFUNCTION(BlueprintCallable, Category = Stats)
	void DecreaseMana(float amount);

	UFUNCTION(BlueprintCallable, Category = Stats)
	void GenerateRage(float amount);

	UFUNCTION(BlueprintCallable, Category = Stats)
	void RemoveRage(float amount);

	UFUNCTION(BlueprintCallable, Category = BaseCharacter)
	void AddEffect(TSubclassOf<UBaseEffectComponent> effectType);

	UFUNCTION(BlueprintCallable, Category = BaseCharacter)
	void RemoveEffect(UBaseEffectComponent* effect);

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

	UFUNCTION(BlueprintCallable, Category = Spells)
	EGaldrarDamageType GetSpellDamageTypeAtIndex(int32 index);

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
