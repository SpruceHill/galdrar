// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "EffectFunctionLibrary.h"
#include "BurnEffectComponent.h"
#include "GasCloudEffectComponent.h"
#include "HealEffectComponent.h"
#include "ManaRegenerationEffectComponent.h"

void UEffectFunctionLibrary::GenerateEffect(ABaseCharacter* character, TSubclassOf<UBaseEffectComponent> effectType)
{
	UBaseEffectComponent* effect = NULL;

	if (effectType->IsChildOf(UBurnEffectComponent::StaticClass()))
	{
		effect = NewObject<UBurnEffectComponent>(character);
	}
	else if (effectType->IsChildOf(UGasCloudEffectComponent::StaticClass()))
	{
		effect = NewObject<UGasCloudEffectComponent>(character);
	}
	else if (effectType->IsChildOf(UHealEffectComponent::StaticClass()))
	{
		effect = NewObject<UHealEffectComponent>(character);
	}
	else if (effectType->IsChildOf(UManaRegenerationEffectComponent::StaticClass()))
	{
		effect = NewObject<UManaRegenerationEffectComponent>(character);
	}

	if (effect)
	{
		character->AddInstanceComponent(effect);
		effect->RegisterComponent();
	}
}

bool UEffectFunctionLibrary::IsDefensive(TSubclassOf<UBaseEffectComponent> effectType)
{
	return effectType.GetDefaultObject()->IsDefensive();
}
