// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "GaldrarHUD.h"
#include "HeroPlayerController.h"
#include "BaseCharacter.h"

void AGaldrarHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AGaldrarHUD::RemoveAOETemplate()
{
	if (AOETemplate) AOETemplate->Destroy();
}

void AGaldrarHUD::RemoveRangeIndicator()
{
	if (rangeIndicator) rangeIndicator->DestroyComponent();
}
