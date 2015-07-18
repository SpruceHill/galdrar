// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "ItemHandler.h"
#include "ManaRegenEffect.h"
#include "EffectFactory.h"

void ItemHandler::ActivateItem(ALoot* item, ABaseCharacter* owner, ABaseCharacter* target)
{
	switch ((int32)item->GetID())
	{
	// Health potion
	case 30002: item->Activate(owner->GetStats(), owner->GetStats()); break;
	// Mana potion
	case 30003: target->AddEffect(EffectFactory::GenerateEffect(target->GetStats(), EffectType::MANA_REGEN)); break;
	}
}
