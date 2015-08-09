// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "OldEffectFactory.h"
#include "BurnEffectComponent.h"


void OldEffectFactory::GenerateEffect(ABaseCharacter* character, TSubclassOf<UBaseEffectComponent> effectType)
{
	if (effectType->IsChildOf(UBurnEffectComponent::StaticClass()))
	{
		NewNamedObject<UBaseEffectComponent>(character, "burn");
		return;
	}
}

bool OldEffectFactory::IsDefensive(EffectType type)
{
	return false;
	//switch (type)
	//{
	//default: return false;
	//}
}
