// Fill out your copyright notice in the Description page of Project Settings.

#include "Galdrar.h"
#include "HeroPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "HeroCharacter.h"
#include "CombatHandler.h"
#include "Attack.h"
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
		// If cursor is over a character
		if (ABaseCharacter* character = dynamic_cast<ABaseCharacter*>(Hit.GetActor()))
		{
			if (AGaldrarHUD* hud = dynamic_cast<AGaldrarHUD*>(GetHUD()))
			{
				hud->SetFocusedCharacter(character);
			}
			if(!(bSelectingUnitTarget || bSelectingGroundTarget))
			CurrentMouseCursor = EMouseCursor::Hand;
		}
		// If cursor is over loot
		else if (ALoot* loot = dynamic_cast<ALoot*>(Hit.GetActor()))
		{
			if (AGaldrarHUD* hud = dynamic_cast<AGaldrarHUD*>(GetHUD()))
			{
				hud->SetFocusedLoot(loot);
			}
			if (!(bSelectingUnitTarget || bSelectingGroundTarget))
			CurrentMouseCursor = EMouseCursor::Hand;
		}
		// Floor, walls etc
		else
		{
			if(!(bSelectingUnitTarget || bSelectingGroundTarget))
			CurrentMouseCursor = DefaultMouseCursor;
			if (AGaldrarHUD* hud = dynamic_cast<AGaldrarHUD*>(GetHUD()))
			{
				hud->SetFocusedCharacter(NULL);
				hud->SetFocusedLoot(NULL);
			}
		}
	}
	// Cursor is outside the map
	else
	{
		if (!(bSelectingUnitTarget || bSelectingGroundTarget))
		CurrentMouseCursor = DefaultMouseCursor;
	}

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
	
	if (targetCharacter)
	{
		// TODO SPELLS ALSO
		AHeroCharacter* hero = Cast<AHeroCharacter>(GetPawn());
		AttackEnemy(targetCharacter, hero->GetWeapon());
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

	InputComponent->BindAction("Spell1", IE_Released, this, &AHeroPlayerController::Spell1);
	InputComponent->BindAction("Spell2", IE_Released, this, &AHeroPlayerController::Spell2);
	InputComponent->BindAction("Spell3", IE_Released, this, &AHeroPlayerController::Spell3);
	InputComponent->BindAction("Spell4", IE_Released, this, &AHeroPlayerController::Spell3);

	InputComponent->BindAction("CancelAction", IE_Released, this, &AHeroPlayerController::CancelAction);
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

		// Walk if far enough or ordered stand still (HACK)
		if (NavSys && ( (Distance > 120.0f) || DestLocation == Pawn->GetActorLocation()))
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
			AttackEnemy(character, hero->GetWeapon());
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

void AHeroPlayerController::AttackEnemy(ABaseCharacter* character, Attack* attack)
{
	AHeroCharacter* hero = Cast<AHeroCharacter>(GetPawn());
	if (hero->GetDistanceTo(character) < attack->GetRange())
	{
		FaceActor(character);
		CombatHandler::AttackEnemy(hero, character, attack);
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

void AHeroPlayerController::Spell1(){ Spell(0); }
void AHeroPlayerController::Spell2(){ Spell(1); }
void AHeroPlayerController::Spell3(){ Spell(2); }
void AHeroPlayerController::Spell4(){ Spell(3); }

void AHeroPlayerController::CancelAction()
{
	bSelectingUnitTarget = false;
	bSelectingGroundTarget = false;
	if (targetCharacter)
	{
		SetNewMoveDestination(GetPawn()->GetActorLocation());
		targetCharacter = NULL;
	}
	else if (targetLoot)
	{
		SetNewMoveDestination(GetPawn()->GetActorLocation());
		targetLoot = NULL;
	}
}

void AHeroPlayerController::Spell(int8 index)
{
	AHeroCharacter* hero = Cast<AHeroCharacter>(GetPawn());
	switch (hero->GetSpell(index)->GetActivation())
	{
	case Spell::Activation::TARGET_UNIT :
		bSelectingGroundTarget = false;
		bSelectingUnitTarget = true;
		CurrentMouseCursor = EMouseCursor::Crosshairs;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Target Unit");
		break;
	
	case Spell::Activation::TARGET_GROUND :
		bSelectingUnitTarget = false;
		bSelectingGroundTarget = true;
		CurrentMouseCursor = EMouseCursor::CardinalCross;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Target Ground");
		break;

	case Spell::Activation::PASSIVE :
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Passive");
		break;

	case Spell::Activation::ATTACK_MODIFIER :
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Attack Modifier");
		break;

	case Spell::Activation::SELF :
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Self");
		break;
	}
}
