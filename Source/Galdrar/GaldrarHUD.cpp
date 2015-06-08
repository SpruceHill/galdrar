// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "GaldrarHUD.h"
#include "HeroPlayerController.h"
#include "EnemyCharacter.h"

void AGaldrarHUD::DrawHUD()
{
	APlayerController* PC = GetOwningPlayerController();
	AHeroPlayerController* HPC = Cast<AHeroPlayerController>(PC);

	DrawHealthbar();
	//DrawAbilitybar();

}

void AGaldrarHUD::DrawHealthbar()
{
	return;
}
