// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "HealEffectComponent.h"
#include "BaseCharacter.h"


// Sets default values for this component's properties
UHealEffectComponent::UHealEffectComponent()
{
	name = "Regeneration";
	desc = "Healing you over time.";
	damage = 2.f;

	duration = 10.f;
	tickRate = 1.f;
	time = 0.f;
	elapsedTime = 0.f;

	damageType = EGaldrarDamageType::PHYSICAL;
	bStackable = false;
	bRemoveOnDamageTaken = false;

	// 4 = Effect, ID = 0003
	ID = 40003;
}

void UHealEffectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	elapsedTime += DeltaTime;
	time += DeltaTime;

	if (time > tickRate)
	{
		time -= tickRate;
		if (ABaseCharacter* character = dynamic_cast<ABaseCharacter*>(GetOwner()))
		{
			character->Heal(damage);
		}
	}

	// If time has run out, delete  this effect.
	if (elapsedTime > duration) MarkPendingKill();
}


