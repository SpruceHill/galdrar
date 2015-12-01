 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GaldrarDamageType.h"
#include "CharacterStatsComponent.h"
#include "BaseWeapon.h"
#include "BaseSpell.h"
#include "BaseTrait.h"
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

	UBaseWeapon* GetWeapon() { return weapon; }

	UCharacterStatsComponent* GetStats() { return stats; }

	UFUNCTION(BlueprintCallable, Category = Stats)
	float GetResistance(EGaldrarDamageType type);

	UFUNCTION(BlueprintCallable, Category = Stats)
	void Heal(float amount);

	UFUNCTION(BlueprintCallable, Category = Stats)
	void Wound(int32 amount, EGaldrarDamageType type, bool crit);

	// Mana / Rage
	
	UFUNCTION(BlueprintCallable, Category = Stats)
	void DecreaseMana(float amount);

	UFUNCTION(BlueprintCallable, Category = Stats)
	void GenerateRage(float amount);

	UFUNCTION(BlueprintCallable, Category = Stats)
	void RemoveRage(float amount);

	// Effects
	
	UFUNCTION(BlueprintCallable, Category = BaseCharacter)
	void AddEffect(TSubclassOf<UBaseEffectComponent> effectType);

	UFUNCTION(BlueprintCallable, Category = BaseCharacter)
	void RemoveEffect(UBaseEffectComponent* effect);

	// RENDER EFFECTS

	UFUNCTION(BlueprintCallable, Category = BaseCharacter)
	void AddEffectRenderState(EEffectRenderState::Type renderState);

	UFUNCTION(BlueprintCallable, Category = BaseCharacter)
	void RemoveEffectRenderState(EEffectRenderState::Type renderState);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = BaseCharacter)
	void SpawnRenderEffect(EEffectRenderState::Type renderState);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = BaseCharacter)
	void DestroyRenderEffect(EEffectRenderState::Type renderState);

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
	bool IsAlive();

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

	UFUNCTION(BlueprintCallable, Category = BaseCharacter)
	void MissedAttack();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = BaseCharacter)
	void OnTakeDamage(EGaldrarDamageType type);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = BaseCharacter)
	void OnDeath();

	UFUNCTION(BlueprintImplementableEvent, Category = BaseCharacter)
	void AttackAnimation();

	UFUNCTION(BlueprintImplementableEvent, Category = BaseCharacter)
	void OnSpellCast(bool directional);

	UFUNCTION(BlueprintImplementableEvent, Category = BaseCharacter)
	void OnStunned();

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
	UBaseSpell* spell1;
	UPROPERTY(BlueprintReadWrite, Category = BaseCharacter)
	UBaseSpell* spell2;
	UPROPERTY(BlueprintReadWrite, Category = BaseCharacter)
	UBaseSpell* spell3;
	UPROPERTY(BlueprintReadWrite, Category = BaseCharacter)
	UBaseSpell* spell4;

	UPROPERTY(BlueprintReadWrite, Category = BaseCharacter)
	UBaseTrait* trait1;
	UPROPERTY(BlueprintReadWrite, Category = BaseCharacter)
	UBaseTrait* trait2;

	UPROPERTY(BlueprintReadWrite, Category = BaseCharacter)
	bool bStunned = false;
	UPROPERTY(BlueprintReadWrite, Category = BaseCharacter)
	bool bSilenced = false;

	UPROPERTY(BlueprintReadWrite, Category = BaseCharacter)
	TArray<TEnumAsByte<EEffectRenderState::Type>> renderStates;

private:
	float stunTime = 0.f;
	float stunDuration = 0.f;

	float silenceTime = 0.f;
	float silenceDuration = 0.f;
};
