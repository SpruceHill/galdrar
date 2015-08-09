// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "BaseCharacter.h"
#include "BaseEffectComponent.h"

class GALDRAR_API OldEffectFactory
{
public:
	static void GenerateEffect(ABaseCharacter* character, TSubclassOf<UBaseEffectComponent> effectType);
	static bool IsDefensive(EffectType type);
};
