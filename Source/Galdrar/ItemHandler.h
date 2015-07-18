// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "Loot.h"
#include "BaseCharacter.h"
#include "HeroCharacter.h"
/**
 * 
 */
class GALDRAR_API ItemHandler
{
public:
	static void ActivateItem(ALoot* item, AHeroCharacter* owner, ABaseCharacter* target);
};
