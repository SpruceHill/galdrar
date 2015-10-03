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
	
	void CreateDamageIndicator(ABaseCharacter* character, const FString& text, FColor indicatorColor, bool crit);

	void CreateCharacterTextPopup(ABaseCharacter* character, const FString& text, FColor indicatorColor);

	void Toast(const FString& text);

	static void SetHUD(AGaldrarHUD* hud);

	static AGaldrarHUD* HUDInstance;
};
