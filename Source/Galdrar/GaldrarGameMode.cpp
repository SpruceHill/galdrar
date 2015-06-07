// Fill out your copyright notice in the Description page of Project Settings.

#include "Galdrar.h"
#include "GaldrarGameMode.h"
#include "HeroPlayerController.h"
#include "BaseCharacter.h"


AgaldrarGameMode::AgaldrarGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Controller
	PlayerControllerClass = AHeroPlayerController::StaticClass();

}

