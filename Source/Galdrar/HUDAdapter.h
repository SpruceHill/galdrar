// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "GaldrarHUD.h"

/**
 * 
 */
class GALDRAR_API HUDAdapter
{
public:
	//static HUDAdapter AdapterInstance;

	AGaldrarHUD* GetHUD();
	
	void CreateDamageIndicator(ABaseCharacter* character, float damage, FColor indicatorColor, bool crit);

	static void SetHUD(AGaldrarHUD* hud);

	static AGaldrarHUD* HUDInstance;
};
