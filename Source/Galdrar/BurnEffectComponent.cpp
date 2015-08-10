// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "BurnEffectComponent.h"
#include "BaseCharacter.h"
#include "CombatHandler.h"


// Sets default values for this component's properties
UBurnEffectComponent::UBurnEffectComponent()
{
	name = "Burning";
	desc = "On fire";
	damage = 5.f;

	duration = 2.f;
	tickRate = 0.5f;
	time = 0.f;
	elapsedTime = 0.f;

	damageType = EGaldrarDamageType::FIRE;
	bStackable = false;
	bPrintDI = false;
	toBePrinted = desc;
	bRemoveOnDamageTaken = false;

	// 4 = Effect, ID = 0001
	ID = 40001;
}

void UBurnEffectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
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

	// If time has run out, delete  this effect.
	if (elapsedTime > duration) Remove();
}
