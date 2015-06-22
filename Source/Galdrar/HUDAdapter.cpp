// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "HUDAdapter.h"

//HUDAdapter HUDAdapter::AdapterInstance;
AGaldrarHUD* HUDAdapter::HUDInstance;

void HUDAdapter::CreateDamageIndicator(ABaseCharacter* character, float damage, FColor indicatorColor, bool crit)
{
	HUDInstance->CreateDamageIndicator(character, damage, indicatorColor, crit);
}

AGaldrarHUD* HUDAdapter::GetHUD()
{
	return HUDInstance;
}

void HUDAdapter::SetHUD(AGaldrarHUD* hud)
{
	HUDInstance = hud;
}
