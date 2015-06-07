// Fill out your copyright notice in the Description page of Project Settings.

#include "Galdrar.h"
#include "GaldrarGameMode.h"
#include "HeroPlayerController.h"
#include "HeroCharacter.h"


AgaldrarGameMode::AgaldrarGameMode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	// Controller
	PlayerControllerClass = AHeroPlayerController::StaticClass();
	DefaultPawnClass = AHeroCharacter::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/AnimStarterPack/BPHeroCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

