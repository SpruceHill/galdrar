// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "ItemHandler.h"
#include "ManaRegenEffect.h"
#include "EffectFactory.h"

void ItemHandler::ActivateItem(ALoot* item, AHeroCharacter* owner, ABaseCharacter* target)
{
	switch ((int32)item->GetID())
	{
	// Health potion
	case 30002: 
		target->AddEffect(EffectType::HEAL);
		owner->RemoveItem(item);
		item->Destroy();
		break;
	// Mana potion
	case 30003: 
		target->AddEffect(EffectType::MANA_REGEN);
		owner->RemoveItem(item);
		item->Destroy();
		break;
	}
}
