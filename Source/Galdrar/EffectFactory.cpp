// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "EffectFactory.h"
#include "BurnEffect.h"
#include "PoisonEffect.h"
#include "HealEffect.h"
#include "ManaRegenEffect.h"

Effect* EffectFactory::GenerateEffect(UCharacterStatsComponent* stats, EffectType type)
{
	switch (type)
	{
	case EffectType::BURNING: return new BurnEffect(stats);
	case EffectType::POISON_MILD: return new PoisonEffect(stats);
	case EffectType::HEAL: return new HealEffect(stats);
	case EffectType::MANA_REGEN: return new ManaRegenEffect(stats);
	}
	return new Effect();
}

bool EffectFactory::IsDefensive(EffectType type)
{
	return false;
	//switch (type)
	//{
	//default: return false;
	//}
}
