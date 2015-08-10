// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "ItemHandler.h"
#include "HealEffectComponent.h"
#include "ManaRegenerationEffectComponent.h"

void ItemHandler::ActivateItem(ALoot* item, AHeroCharacter* owner, ABaseCharacter* target)
{
	switch (item->GetID())
	{
	// Health potion
	case 30002:
		target->AddEffect(UHealEffectComponent::StaticClass());
		owner->RemoveItem(item);
		item->Destroy();
		break;
	// Mana potion
	case 30003: 
		target->AddEffect(UManaRegenerationEffectComponent::StaticClass());
		owner->RemoveItem(item);
		item->Destroy();
		break;
	}
}
