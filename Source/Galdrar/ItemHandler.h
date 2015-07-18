// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "Loot.h"
#include "BaseCharacter.h"
/**
 * 
 */
class GALDRAR_API ItemHandler
{
public:
	static void ActivateItem(ALoot* item, ABaseCharacter* owner, ABaseCharacter* target);
};
