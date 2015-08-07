// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "EffectType.h"
#include "Effect.h"
#include "CharacterStatsComponent.h"

class GALDRAR_API EffectFactory
{
public:
	static Effect* GenerateEffect(UCharacterStatsComponent* stats, EffectType type);
	static bool IsDefensive(EffectType type);
};
