 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GaldrarDamageType.h"
#include "Attack.h"
#include <list>
#include <algorithm>
#include "CharacterStatsComponent.h"
#include "BaseWeapon.h"
#include "BaseSpell.h"
#include "BaseEffectComponent.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS()
class GALDRAR_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = BaseCharacter)
		void InitializeSpells(TSubclassOf<UBaseSpell> spell1, TSubclassOf<UBaseSpell> spell2,
		TSubclassOf<UBaseSpell> spell3, TSubclassOf<UBaseSpell> spell4);

	virtual void Tick(float DeltaSeconds) override;

	FString GetName() { return name; }

	float GetDamage() { return weapon->GetDamage(); }

	UBaseWeapon* GetWeapon() { return weapon; }

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
	void DecreaseMana(float amount);

	UFUNCTION(BlueprintCallable, Category = Stats)
	void GenerateRage(float amount);

	UFUNCTION(BlueprintCallable, Category = Stats)
	void RemoveRage(float amount);

	UFUNCTION(BlueprintCallable, Category = BaseCharacter)
	void AddEffect(TSubclassOf<UBaseEffectComponent> effectType);

	UFUNCTION(BlueprintCallable, Category = BaseCharacter)
	void RemoveEffect(UBaseEffectComponent* effect);

	UBaseSpell* GetSpell(int8 index)
	{
		if (index == 0) return spell1;
		else if (index == 1) return spell2;
		else if (index == 2) return spell3;
		else return spell4;
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
	void OnTakeDamage(EGaldrarDamageType type);

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
	
	UPROPERTY(BlueprintReadWrite, Category = BaseCharacter)
	UBaseWeapon* weapon;
	
	UPROPERTY(BlueprintReadWrite, Category = BaseCharacter)
	TArray<UBaseSpell*> spells;

	UPROPERTY(BlueprintReadWrite, Category = BaseCharacter)
	UBaseSpell* spell1;
	UPROPERTY(BlueprintReadWrite, Category = BaseCharacter)
	UBaseSpell* spell2;
	UPROPERTY(BlueprintReadWrite, Category = BaseCharacter)
	UBaseSpell* spell3;
	UPROPERTY(BlueprintReadWrite, Category = BaseCharacter)
	UBaseSpell* spell4;

	UPROPERTY(BlueprintReadWrite, Category = BaseCharacter)
	bool bStunned = false;
	UPROPERTY(BlueprintReadWrite, Category = BaseCharacter)
	bool bSilenced = false;

private:
	float stunTime = 0.f;
	float stunDuration = 0.f;

	float silenceTime = 0.f;
	float silenceDuration = 0.f;
};
