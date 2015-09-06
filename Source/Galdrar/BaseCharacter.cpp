// Fill out your copyright notice in the Description page of Project Settings.

#include "Galdrar.h"
#include "BaseCharacter.h"
#include "HUDAdapter.h"
#include "GaldrarColor.h"
#include "EffectFunctionLibrary.h"
#include "DragonsBreath.h"

void ABaseCharacter::InitializeSpells(TSubclassOf<UBaseSpell> spell1, TSubclassOf<UBaseSpell> spell2,
	TSubclassOf<UBaseSpell> spell3, TSubclassOf<UBaseSpell> spell4)
{
	this->spell1 = NewObject<UDragonsBreath>(this);
	this->spell2 = NewObject<UDragonsBreath>(this);
	this->spell3 = NewObject<UDragonsBreath>(this);
	this->spell4 = NewObject<UDragonsBreath>(this);
}

void ABaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	GetCharacterMovement()->MaxWalkSpeed = stats->movementSpeed;
	GetCharacterMovement()->RotationRate = FRotator(0.f, stats->rotationRate, 0.f);

	// Mana regen
	if (stats->mana < stats->maxMana - stats->rage) stats->mana += stats->manaReg*DeltaSeconds;
	// Rage Deregen
	if (stats->rage > 0) RemoveRage(stats->rageDegenerationRate*DeltaSeconds);

	// Tick stun
	if (bStunned)
	{
		stunTime += DeltaSeconds;
		if (stunTime >= stunDuration)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, name + " is no longer stunned");
			bStunned = false;
			stunTime = 0.f;
			stunDuration = 0.f;
		}
	}
}

float ABaseCharacter::GetResistance(EGaldrarDamageType type)
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

void ABaseCharacter::Heal(float amount)
{
	HUDAdapter HA;
	HA.CreateDamageIndicator(this, "+"+FString::FromInt(amount), UGaldrarColor::GetHealColor(), false);
	if (stats->health + amount > stats->maxHealth)
	{
		stats->health = stats->maxHealth;
	}
	else
	{
		stats->health += amount;
	}
}

void ABaseCharacter::Wound(int32 amount, EGaldrarDamageType type, bool crit)
{
	HUDAdapter HA;
	HA.CreateDamageIndicator(this, FString::FromInt(amount), UGaldrarColor::GetDamageTypeColor(type), crit);

	stats->health -= amount;

	OnTakeDamage(type);

	// Build rage
	GenerateRage(amount * stats->rageGenerationMultiplier);

	// Remove damage sensitive effects
	for (UActorComponent * ac : GetActiveEffectComponents())
	{
		UBaseEffectComponent* ec = Cast<UBaseEffectComponent>(ac);
		if (ec->bRemoveOnDamageTaken) ec->Remove();
	}

	// Fatal blow
	if (stats->health <= 0 && stats->health + amount > 0)
	{
		DisableInput(Cast<APlayerController>(GetController()));
		OnDeath();

		for (UActorComponent* ac : GetActiveEffectComponents())
		{
			ac->MarkPendingKill();
		}

		// Make Ragdoll
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
		GetMesh()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
		GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
		GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Ignore);
		GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Ignore);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		GetMesh()->SetSimulatePhysics(true);
		CursorHitbox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ABaseCharacter::DecreaseMana(float amount)
{
	if (stats->mana - amount <= 0.f) stats->mana = 0.f;
	else stats->mana -= amount;
}

void ABaseCharacter::GenerateRage(float amount)
{
	// If rage bar is full
	if (stats->rage + (amount * stats->damageMultiplier) > stats->maxMana)
	{
		stats->rage = stats->maxMana;
		stats->mana = 0;
	}
	else
	{
		stats->rage += (amount * stats->damageMultiplier);

		// If mana should be affected
		if (stats->maxMana - stats->rage < stats->mana)
		{
			if (stats->mana - amount < 0) stats->mana = 0;
			//else stats->mana -= amount;
			else stats->mana = stats->maxMana-stats->rage;
		}
	}
}

void ABaseCharacter::RemoveRage(float amount)
{
	if (stats->rage - amount < 0.f)
	{
		stats->rage = 0.f;
	}
	else
	{
		stats->rage -= amount;
	}
}

void ABaseCharacter::Stun(float duration)
{
	if (!bStunned)
	{
		HUDAdapter HA;
		HA.CreateDamageIndicator(this, "Stunned", FColor::White, false);
	}
	// Extend stun time if new stun is applied
	if (stunDuration - stunTime < duration)
	{
		stunDuration = stunTime + duration;
		bStunned = true;
	}
}

void ABaseCharacter::Silence(float duration)
{
	if (!bSilenced)
	{
		HUDAdapter HA;
		HA.CreateDamageIndicator(this, "Silenced", FColor::White, false);
	}
	// Extend silence time if new silence is applied
	if (silenceDuration - silenceTime < duration)
	{
		silenceDuration = silenceTime + duration;
		bSilenced = true;
	}
}

void ABaseCharacter::AddEffect(TSubclassOf<UBaseEffectComponent> effectType)
{
	if (stats->health <= 0) return;

	// Character restist effect if the damage it deals is below 1 after resistance check.
	if (int32(effectType.GetDefaultObject()->GetDamage() 
		* (1 - (GetResistance(effectType.GetDefaultObject()->GetDamageType())
		/ 100.f))) < 1)
	{
		HUDAdapter HA;
		HA.CreateDamageIndicator(this, "Resisted", UGaldrarColor::GetDamageTypeColor(effectType.GetDefaultObject()->GetDamageType()), false);
		return;
	}

	bool found = false;
	for (UActorComponent* ac : GetActiveEffectComponents())
	{
		UBaseEffectComponent* ec = Cast<UBaseEffectComponent>(ac);
		
		if (ec->IsA(effectType))
		{
			found = true;
			if (ec->bStackable)
			{
				UEffectFunctionLibrary::GenerateEffect(this, effectType);
			}
			else
				ec->ResetTimer();
		}
	}
	if (!found)
	{
		UEffectFunctionLibrary::GenerateEffect(this, effectType);
	}
}

void ABaseCharacter::RemoveEffect(UBaseEffectComponent* effect)
{
	if (GetActiveEffectComponents().Contains(effect))
		effect->Remove();
}

void ABaseCharacter::AddEffectRenderState(EEffectRenderState::Type renderState)
{
	if (!renderStates.Contains(renderState)) SpawnRenderEffect(renderState);
	renderStates.Add(renderState);
}

void ABaseCharacter::RemoveEffectRenderState(EEffectRenderState::Type renderState)
{
	renderStates.Remove(renderState);
	if (!renderStates.Contains(renderState))
	{
		DestroyRenderEffect(renderState);
	}
}

float ABaseCharacter::GetHealth()
{
	return stats->health;
}

float ABaseCharacter::GetMaxHealth()
{
	return stats->maxHealth;
}

float ABaseCharacter::GetMaxMana()
{
	return stats->maxMana;
}

float ABaseCharacter::GetMana()
{
	return stats->mana;
}

int32 ABaseCharacter::GetSpellIdAtIndex(int32 index)
{
	if (index == 0) return spell1->GetID();
	else if (index == 1) return spell2->GetID();
	else if (index == 2) return spell3->GetID();
	else return spell4->GetID();
	//return (spells[index] ? spells[index]->GetID() : -1);
}

float ABaseCharacter::GetSpellCooldownAtIndex(int32 index)
{
	if (index == 0) return spell1->GetCooldown();
	else if (index == 1) return spell2->GetCooldown();
	else if (index == 2) return spell3->GetCooldown();
	else return spell4->GetCooldown();
	//return (spells[index] ? spells[index]->GetCooldown() : 1);
}

float ABaseCharacter::GetSpellTimeAtIndex(int32 index)
{
	if (index == 0) return spell1->GetTime();
	else if (index == 1) return spell2->GetTime();
	else if (index == 2) return spell3->GetTime();
	else return spell4->GetTime();
	//return (spells[index] ? spells[index]->GetTime() : 1);
}

FString ABaseCharacter::GetSpellNameAtIndex(int32 index)
{
	if (index == 0) return spell1->GetName();
	else if (index == 1) return spell2->GetName();
	else if (index == 2) return spell3->GetName();
	else return spell4->GetName();
}

FString ABaseCharacter::GetSpellDescAtIndex(int32 index)
{
	if (index == 0) return spell1->GetDesc();
	else if (index == 1) return spell2->GetDesc();
	else if (index == 2) return spell3->GetDesc();
	else return spell4->GetDesc();
}

float ABaseCharacter::GetSpellManaCostAtIndex(int32 index)
{
	if (index == 0) return spell1->GetManaCost();
	else if (index == 1) return spell2->GetManaCost();
	else if (index == 2) return spell3->GetManaCost();
	else return spell4->GetManaCost();
}

EGaldrarDamageType ABaseCharacter::GetSpellDamageTypeAtIndex(int32 index)
{
	if (index == 0) return spell1->GetDamageType();
	else if (index == 1) return spell2->GetDamageType();
	else if (index == 2) return spell3->GetDamageType();
	else return spell4->GetDamageType();
}

bool ABaseCharacter::IsStunned()
{
	return bStunned;
}

bool ABaseCharacter::IsSilenced()
{
	return bSilenced;
}

TArray<UActorComponent*> ABaseCharacter::GetActiveEffectComponents()
{
	return GetComponentsByClass(UBaseEffectComponent::StaticClass());
}
