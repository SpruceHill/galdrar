// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "HUDAdapter.h"

//HUDAdapter HUDAdapter::AdapterInstance;
AGaldrarHUD* HUDAdapter::HUDInstance;

void HUDAdapter::CreateDamageIndicator(ABaseCharacter* character, const FString& text, FColor indicatorColor, bool crit)
{
	HUDInstance->CreateDamageIndicator(character, text, indicatorColor, crit);
}

void HUDAdapter::CreateCharacterTextPopup(ABaseCharacter* character, const FString& text, FColor indicatorColor)
{
	HUDInstance->CreateCharacterTextPopup(character, text, indicatorColor);
}

void HUDAdapter::Toast(const FString& text)
{
	HUDInstance->Toast(text);
}

AGaldrarHUD* HUDAdapter::GetHUD()
{
	return HUDInstance;
}

void HUDAdapter::SetHUD(AGaldrarHUD* hud)
{
	HUDInstance = hud;
}
