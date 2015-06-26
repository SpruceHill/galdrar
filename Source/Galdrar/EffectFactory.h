// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "EffectType.h"
#include "Effect.h"
#include "BurnEffect.h"
#include "CharacterStats.h"

class GALDRAR_API EffectFactory
{
public:
	static Effect* GenerateEffect(CharacterStats* stats, EffectType type);
};
