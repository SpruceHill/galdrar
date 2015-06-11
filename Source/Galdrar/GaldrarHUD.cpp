// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "GaldrarHUD.h"
#include "HeroPlayerController.h"
#include "BaseCharacter.h"

void AGaldrarHUD::DrawHUD()
{
	Super::DrawHUD();

	//if (focusedCharacter) DrawHealthbar(focusedCharacter);
	//focusedCharacter = NULL;
}

void AGaldrarHUD::DrawHealthbar(ABaseCharacter* baseCharacter)
{
	//if(baseCharacter) baseCharacter->drawHealthbar = true;
}
