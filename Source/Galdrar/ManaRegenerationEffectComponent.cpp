// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "ManaRegenerationEffectComponent.h"
#include "BaseCharacter.h"

// Sets default values for this component's properties
UManaRegenerationEffectComponent::UManaRegenerationEffectComponent()
{
	name = "Mana Regeneration";
	desc = "+3 mana regeneration for 10 seconds.";
	damage = 100.f;

	duration = 10.f;
	elapsedTime = 0.f;

	damageType = EGaldrarDamageType::NONE;
	bStackable = false;
	bRemoveOnDamageTaken = true;

	// 4 = Effect, ID = 0004
	ID = 40004;

	if (ABaseCharacter* character = dynamic_cast<ABaseCharacter*>(GetOwner()))
	{
		character->GetStats()->manaReg += 3;
	}
}

void UManaRegenerationEffectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	elapsedTime += DeltaTime;

	// Remove effect
	if (ABaseCharacter* character = dynamic_cast<ABaseCharacter*>(GetOwner()))
	{
		if (elapsedTime >= duration || character->GetStats()->mana >= character->GetStats()->maxMana)
		{
			Remove();
		}
	}
}

void UManaRegenerationEffectComponent::Remove()
{
	if (ABaseCharacter* character = dynamic_cast<ABaseCharacter*>(GetOwner()))
	{
		character->GetStats()->manaReg -= 3;
	}
	MarkPendingKill();
	GetOwner()->RemoveOwnedComponent(this);
}


