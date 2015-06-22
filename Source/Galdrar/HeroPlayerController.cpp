// Fill out your copyright notice in the Description page of Project Settings.

#include "Galdrar.h"
#include "HeroPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "HeroCharacter.h"
#include "CombatHandler.h"
#include "GaldrarHUD.h"
#include "GaldrarColor.h"

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

	if (AGaldrarHUD* hud = dynamic_cast<AGaldrarHUD*>(GetHUD()))
	{
		HA.SetHUD(hud);
	}

	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		if (ABaseCharacter* character = dynamic_cast<ABaseCharacter*>(Hit.GetActor()))
		{
			if (AGaldrarHUD* hud = dynamic_cast<AGaldrarHUD*>(GetHUD()))
			{
				hud->SetFocusedCharacter(character);
			}
			CurrentMouseCursor = EMouseCursor::Hand;
		}
		else if (ALoot* loot = dynamic_cast<ALoot*>(Hit.GetActor()))
		{
			if (AGaldrarHUD* hud = dynamic_cast<AGaldrarHUD*>(GetHUD()))
			{
				hud->SetFocusedLoot(loot);
			}
			CurrentMouseCursor = EMouseCursor::Hand;
		}
		else
		{
			// Floor, walls etc
			CurrentMouseCursor = DefaultMouseCursor;
			if (AGaldrarHUD* hud = dynamic_cast<AGaldrarHUD*>(GetHUD()))
			{
				hud->SetFocusedCharacter(NULL);
				hud->SetFocusedLoot(NULL);
			}
		}
	}
	else
	{
		// If outside the map
		CurrentMouseCursor = DefaultMouseCursor;
	}

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
	if (targetCharacter)
	{
		Attack(targetCharacter);
	}
	else if (targetLoot)
	{
		Pickup(targetLoot);
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
			Attack(character);
		}
		else if (ALoot* loot = dynamic_cast<ALoot*>(Hit.GetActor()))
		{
			Pickup(loot);
		}
		else
		{
			// set flag to keep updating destination until released
			targetCharacter = NULL;
			targetLoot = NULL;
			bMoveToMouseCursor = true;
		}
	}
}

void AHeroPlayerController::Attack(ABaseCharacter* character)
{
	AHeroCharacter* hero = Cast<AHeroCharacter>(GetPawn());
	if (hero->GetDistanceTo(character) < hero->GetWeapon()->GetRange())
	{
		/*// Rotate attacker towards the defender
		FVector newLookAt = character->GetActorLocation().operator-=(hero->GetActorLocation());
		newLookAt.Z = 1; // Make sure character is always upright (attacking on stairs etc.)
		hero->SetActorRotation(newLookAt.Rotation());*/
		FaceActor(character);
		CombatHandler::AttackEnemy(hero, character, hero->GetWeapon());
		//UGameplayStatics::ApplyDamage(character, damage, NULL, hero, UDamageType::StaticClass());

		/*if (AGaldrarHUD* hud = dynamic_cast<AGaldrarHUD*>(GetHUD()))
		{
			hud->CreateDamageIndicator(character, damage, GaldrarColor::GetDamageTypeColor(hero->GetWeapon()->GetDamageType()),
				CombatHandler::IsCritical(hero->GetActorForwardVector(), character->GetActorForwardVector()));
		}*/
		targetCharacter = NULL;
	}
	else // Not in range
	{
		targetCharacter = character;
		SetNewMoveDestination(targetCharacter->GetActorLocation());
	}
}

void AHeroPlayerController::FaceActor(AActor* actorToFace)
{
	// Rotate attacker towards the defender
	FVector newLookAt = actorToFace->GetActorLocation().operator-=(GetPawn()->GetActorLocation());
	newLookAt.Z = 1; // Make sure character is always upright (attacking on stairs etc.)
	GetPawn()->SetActorRotation(newLookAt.Rotation());
}

void AHeroPlayerController::Pickup(ALoot* loot)
{
	AHeroCharacter* hero = Cast<AHeroCharacter>(GetPawn());
	if (hero->GetDistanceTo(loot) < pickUpRange)
	{
		if (AValuable* valuable = dynamic_cast<AValuable*>(loot))
		{
			hero->AddValuable(valuable);
		}
		loot->Destroy();
		targetLoot = NULL;
	}
	else // Not in range
	{
		targetLoot = loot;
		SetNewMoveDestination(targetLoot->GetActorLocation());
	}
}

void AHeroPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}
