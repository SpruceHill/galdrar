// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "GasCloudEffectComponent.h"
#include "BaseCharacter.h"
#include "CombatHandler.h"

// Sets default values for this component's properties
UGasCloudEffectComponent::UGasCloudEffectComponent()
{
	name = "Poisoned";
	desc = "You are poisoned – taking damage over time.";
	damage = 3.f;

	duration = 10.f;
	tickRate = 1.f;
	time = 0.f;
	elapsedTime = 0.f;

	damageType = EGaldrarDamageType::POISON;
	bStackable = false;
	bRemoveOnDamageTaken = false;

	// 4 = Effect, ID = 0002
	ID = 40002;
}

void UGasCloudEffectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	elapsedTime += DeltaTime;
	time += DeltaTime;

	if (time > tickRate)
	{
		time -= tickRate;
		if (ABaseCharacter* character = dynamic_cast<ABaseCharacter*>(GetOwner()))
		{
			character->Wound(CombatHandler::CalcDamage(damage, character->GetResistance(damageType), 0, false), damageType, false);
		}
	}

	// If time has run out, delete this effect.
	if (elapsedTime > duration) Remove();
}
