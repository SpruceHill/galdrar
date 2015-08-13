// Fill out your copyright notice in the Description page of Project Settings.

#include "Galdrar.h"
#include "BaseCharacter.h"
#include "HUDAdapter.h"
#include "GaldrarColor.h"
#include "EffectFunctionLibrary.h"

void ABaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	GetCharacterMovement()->MaxWalkSpeed = stats->movementSpeed;
	GetCharacterMovement()->RotationRate = FRotator(0.f, stats->rotationRate, 0.f);

	// Mana regen
	if (stats->mana < stats->maxMana) stats->mana += stats->manaReg*DeltaSeconds;
	// Rage Deregen
	if (stats->rage > 0) RemoveRage(stats->rageDegenerationRate*DeltaSeconds);

	// Tick spells
	for (Spell* s : spells)
	{
		if (s) s->Tick(DeltaSeconds);
	}

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

void ABaseCharacter::SetHealth(float newHealth)
{
	stats->health = newHealth;
}

void ABaseCharacter::SetMana(float newMana)
{
	stats->mana = newMana;
}

void ABaseCharacter::DecreaseMana(float amount)
{
	if (stats->mana - amount <= 0.f) stats->mana = 0.f;
	else stats->mana -= amount;
}

void ABaseCharacter::GenerateRage(float amount)
{
	// If rage bar is full
	if (stats->rage + amount > stats->defaultMaxMana)
	{
		stats->rage = stats->defaultMaxMana;
		stats->maxMana = 0;
		stats->mana = 0;
	}
	else
	{
		stats->rage += amount;

		// Cap mana to new max value if nesessary
		if (stats->mana > stats->maxMana - amount)
		{
			stats->mana = stats->maxMana - amount;
		}
		else
		{
			stats->mana -= amount;
		}
		stats->maxMana -= amount;
	}
}

void ABaseCharacter::RemoveRage(float amount)
{
	if (stats->rage - amount < 0.f)
	{
		stats->maxMana -= stats->rage - amount;
		stats->rage = 0.f;
	}
	else
	{
		stats->maxMana += amount;
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
	if (stats->maxMana - stats->rage < stats->mana) return (stats->maxMana - stats->rage);
	else return stats->mana;
}


int32 ABaseCharacter::GetSpellIdAtIndex(int32 index)
{
	return (spells[index] ? spells[index]->GetID() : -1);
}

float ABaseCharacter::GetSpellCooldownAtIndex(int32 index)
{
	return (spells[index] ? spells[index]->GetCooldown() : 1);
}

float ABaseCharacter::GetSpellTimeAtIndex(int32 index)
{
	return (spells[index] ? spells[index]->GetTime() : 1);
}

FString ABaseCharacter::GetSpellNameAtIndex(int32 index)
{
	return spells[index]->GetName();
}

FString ABaseCharacter::GetSpellDescAtIndex(int32 index)
{
	return spells[index]->GetDesc();
}

float ABaseCharacter::GetSpellManaCostAtIndex(int32 index)
{
	return spells[index]->GetManaCost();
}

EGaldrarDamageType ABaseCharacter::GetSpellDamageTypeAtIndex(int32 index)
{
	return spells[index]->GetDamageType();
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
