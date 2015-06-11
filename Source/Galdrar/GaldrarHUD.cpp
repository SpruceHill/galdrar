// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "GaldrarHUD.h"
#include "HeroPlayerController.h"
#include "BaseCharacter.h"

void AGaldrarHUD::DrawHUD()
{
	Super::DrawHUD();
//	APlayerController* PC = GetOwningPlayerController();
//	AHeroPlayerController* HPC = Cast<AHeroPlayerController>(PC);
	DrawHealthbar(focusedCharacter);
}

void AGaldrarHUD::DrawHealthbar(ABaseCharacter* baseCharacter)
{
	if (focusedCharacter) GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, baseCharacter->GetName() + " is in focus");
	focusedCharacter = NULL;
}
