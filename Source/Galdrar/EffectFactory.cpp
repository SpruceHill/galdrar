// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "EffectFactory.h"
#include "BurnEffect.h"
#include "PoisonEffect.h"

Effect* EffectFactory::GenerateEffect(CharacterStats* stats, EffectType type)
{
	switch (type)
	{
	case EffectType::BURNING: return new BurnEffect(stats);
	case EffectType::POISON_MILD: return new PoisonEffect(stats);
	}
	return new Effect();
}
