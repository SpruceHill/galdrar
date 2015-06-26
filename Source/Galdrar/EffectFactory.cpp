// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "EffectFactory.h"

Effect* EffectFactory::GenerateEffect(CharacterStats* stats, EffectType type)
{
	switch (type)
	{
	case EffectType::BURNING: return new BurnEffect(stats);
	}
	return new Effect();
}
