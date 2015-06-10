// Fill out your copyright notice in the Description page of Project Settings.

#include "Galdrar.h"
#include "HeroPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "HeroCharacter.h"
#include "CombatHandler.h"

AHeroPlayerController::AHeroPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	bEnableMouseOverEvents = true;

	bShouldZoom = false;
	targetZoom = zoomMax;
}

void AHeroPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

/*	FHitResult TraceResult(ForceInit);
	GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Camera), true, TraceResult);
	if (TraceResult.GetActor())
	{
		if (ABaseCharacter* character = dynamic_cast<ABaseCharacter*>(TraceResult.GetActor()))
		{
			//Do not attack self
			if (character != GetPawn())
			{
				character->drawHealthbar = true;
			}
		}
	}*/

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}

	// Camera smooth zoom
	if (bShouldZoom)
	{
		AHeroCharacter* hero = Cast<AHeroCharacter>(GetPawn());
		if (hero->GetCameraBoom()->TargetArmLength < targetZoom){
			hero->SetCameraBoom(hero->GetCameraBoom()->TargetArmLength + zoomSpeed);
		}
		else if (hero->GetCameraBoom()->TargetArmLength > targetZoom)
		{
			hero->SetCameraBoom(hero->GetCameraBoom()->TargetArmLength - zoomSpeed);
		}
		else
		{
			bShouldZoom = false;
		}
	}
}

void AHeroPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &AHeroPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &AHeroPlayerController::OnSetDestinationReleased);

	InputComponent->BindAction("ZoomIn", IE_Released, this, &AHeroPlayerController::ZoomIn);
	InputComponent->BindAction("ZoomOut", IE_Released, this, &AHeroPlayerController::ZoomOut);
}

void AHeroPlayerController::Zoom(float delta)
{
	// Clamping zoom between zoomMin and zoomMax
	if ((delta < 0 && (targetZoom > zoomMin))
			|| (delta > 0 && (targetZoom < zoomMax)))
	{
		bShouldZoom = true;
		targetZoom += delta;
	}
}

void AHeroPlayerController::MoveToMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if(Hit.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void AHeroPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const Pawn = GetPawn();
	if (Pawn)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, Pawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (NavSys && (Distance > 120.0f))
		{
			NavSys->SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void AHeroPlayerController::OnSetDestinationPressed()
{

	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		if (ABaseCharacter* character = dynamic_cast<ABaseCharacter*>(Hit.GetActor()))
		{
			AHeroCharacter* hero = Cast<AHeroCharacter>(GetPawn());
			CombatHandler::AttackEnemy(hero, character, hero->GetWeapon(), false);
		}
		else
		{
			// set flag to keep updating destination until released
			bMoveToMouseCursor = true;
		}
	}




	/*
	FHitResult TraceResult(ForceInit);
	GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Camera), true, TraceResult);
	if (TraceResult.GetActor())
	{
		if (ABaseCharacter* character = dynamic_cast<ABaseCharacter*>(TraceResult.GetActor())) 
		{
			//Do not attack self
			if (character != GetPawn())
			{
				AHeroCharacter* hero = Cast<AHeroCharacter>(GetPawn());
				CombatHandler::AttackEnemy(hero, character, hero->GetWeapon(), false);
			}
		}
		else
		{
			// set flag to keep updating destination until released
			bMoveToMouseCursor = true;
		}
	}*/
}

void AHeroPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}
