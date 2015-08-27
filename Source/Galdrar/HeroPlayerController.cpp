// Fill out your copyright notice in the Description page of Project Settings.

#include "Galdrar.h"
#include "HeroPlayerController.h"
#include "AI/Navigation/NavigationSystem.h"
#include "HeroCharacter.h"
#include "CombatHandler.h"
#include "GaldrarHUD.h"
#include "GaldrarColor.h"
#include "ItemHandler.h"
#include "EffectFunctionLibrary.h"

AHeroPlayerController::AHeroPlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	bEnableMouseOverEvents = true;

	bShouldZoom = false;
	targetZoom = zoomMax;

	bSelectingUnitTarget = false;
	bSelectingGroundTarget = false;

	groundTarget = FVector::ZeroVector;
}

void AHeroPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	UpdateCursorOverState();

	AHeroCharacter* hero = Cast<AHeroCharacter>(GetPawn());

	bStunned = hero->IsStunned();
	if (bStunned) DisableInput(this);
	else EnableInput(this);

	// Keep updating the destination every tick while desired
	if (bMoveToMouseCursor && !bStunned)
	{
		MoveToMouseCursor();
	}
	
	if (groundTarget != FVector::ZeroVector && !bStunned)
	{
		if (scheduledAttack) 
			AttackGround(groundTarget, scheduledAttack);
	}
	else if (targetCharacter && !bStunned)
	{
		AttackEnemy(targetCharacter, scheduledAttack);
	}
	else if (targetLoot && !bStunned)
	{
		Pickup(targetLoot);
	}

	// Camera smooth zoom
	if (bShouldZoom)
	{
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

void AHeroPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	if (AGaldrarHUD* hud = dynamic_cast<AGaldrarHUD*>(GetHUD()))
	{
		HA.SetHUD(hud);
	}
}

void AHeroPlayerController::UpdateCursorOverState()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		if (bSelectingGroundTarget)
		{
			CurrentMouseCursor = EMouseCursor::CardinalCross;
		}
		else if (bSelectingUnitTarget)
		{
			CurrentMouseCursor = EMouseCursor::Crosshairs;
		}
		// If cursor is over a character
		//if (Hit.GetActor() != GetPawn())
		//{
			if (ABaseCharacter* character = dynamic_cast<ABaseCharacter*>(Hit.GetActor()))
			{
				if (AGaldrarHUD* hud = dynamic_cast<AGaldrarHUD*>(GetHUD()))
				{
					hud->SetFocusedCharacter(character);
				}

				// Set cursor style when on character
				if (!bSelectingGroundTarget)
					CurrentMouseCursor = (bSelectingUnitTarget ? EMouseCursor::EyeDropper : EMouseCursor::Hand);
			}
		//}
		// If cursor is over loot
		else if (ALoot* loot = dynamic_cast<ALoot*>(Hit.GetActor()))
		{
			if (AGaldrarHUD* hud = dynamic_cast<AGaldrarHUD*>(GetHUD()))
			{
				hud->SetFocusedLoot(loot);
			}

			// Set cursor style when on loot
			if (!(bSelectingUnitTarget || bSelectingGroundTarget)) CurrentMouseCursor = EMouseCursor::Hand;
		}
		// Floor, walls etc
		else
		{
			if (!(bSelectingUnitTarget || bSelectingGroundTarget))
			{
				CurrentMouseCursor = DefaultMouseCursor;
			}

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
		CurrentMouseCursor = EMouseCursor::SlashedCircle;
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

	InputComponent->BindAction("Spell1", IE_Pressed, this, &AHeroPlayerController::Spell1);
	InputComponent->BindAction("Spell2", IE_Pressed, this, &AHeroPlayerController::Spell2);
	InputComponent->BindAction("Spell3", IE_Pressed, this, &AHeroPlayerController::Spell3);
	InputComponent->BindAction("Spell4", IE_Pressed, this, &AHeroPlayerController::Spell4);

	InputComponent->BindAction("CancelAction", IE_Pressed, this, &AHeroPlayerController::CancelAction);

	InputComponent->BindAction("Inventory1", IE_Pressed, this, &AHeroPlayerController::Inventory1);
	InputComponent->BindAction("Inventory2", IE_Pressed, this, &AHeroPlayerController::Inventory2);
	InputComponent->BindAction("Inventory3", IE_Pressed, this, &AHeroPlayerController::Inventory3);
	InputComponent->BindAction("Inventory4", IE_Pressed, this, &AHeroPlayerController::Inventory4);
	InputComponent->BindAction("Inventory5", IE_Pressed, this, &AHeroPlayerController::Inventory5);
	InputComponent->BindAction("Inventory6", IE_Pressed, this, &AHeroPlayerController::Inventory6);

	InputComponent->BindAction("BloodVial", IE_Pressed, this, &AHeroPlayerController::UseBloodVial);
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
	scheduledAttack = NULL;
	targetCharacter = NULL;
	targetLoot = NULL;
	groundTarget = FVector::ZeroVector;

	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		if (bSelectingGroundTarget)
		{
			AttackGround(Hit.Location, primedAttack);
			primedAttack = NULL;
		}
		else if (ABaseCharacter* character = dynamic_cast<ABaseCharacter*>(Hit.GetActor()))
		{
			//if (character != GetPawn())
			//{
				if (!primedAttack)
				{
					AHeroCharacter* hero = Cast<AHeroCharacter>(GetPawn());
					primedAttack = hero->GetWeapon();
				}
				AttackEnemy(character, primedAttack);
				primedAttack = NULL;
			//}
		}
		else if (ALoot* loot = dynamic_cast<ALoot*>(Hit.GetActor()))
		{
			primedAttack = NULL;
			Pickup(loot);
		}
		else
		{
			// set flag to keep updating destination until released
			bMoveToMouseCursor = true;
		
			primedAttack = NULL;

			if (AGaldrarHUD* hud = dynamic_cast<AGaldrarHUD*>(GetHUD()))
			{
				hud->CreateMovementLocationIndicator(Hit.Location);
			}

		}
		if (AGaldrarHUD* hud = dynamic_cast<AGaldrarHUD*>(GetHUD()))
		{
			hud->RemoveAOETemplate();
			hud->RemoveRangeIndicator();
		}
		bSelectingGroundTarget = false;
		bSelectingUnitTarget = false;
	}
}

void AHeroPlayerController::AttackEnemy(ABaseCharacter* character, UAttackComponent* attack)
{
	AHeroCharacter* hero = Cast<AHeroCharacter>(GetPawn());
	if (hero->GetDistanceTo(character) < attack->GetRange())
	{
		// Stop moving (HACK)
		SetNewMoveDestination(hero->GetActorLocation());

		FaceActor(character);
		hero->AttackAnimation();
		CombatHandler::AttackEnemy(hero, character, attack);
		attack->ActivateAttack(FVector::ZeroVector, character);

		targetCharacter = NULL;
		primedAttack = NULL;
		scheduledAttack = NULL;
	}
	else // Not in range
	{
		bSelectingUnitTarget = false;
		bSelectingUnitTarget = false;

		if (AGaldrarHUD* hud = dynamic_cast<AGaldrarHUD*>(GetHUD()))
		{
			hud->RemoveAOETemplate();
			hud->RemoveRangeIndicator();
		}

		scheduledAttack = attack;
		targetCharacter = character;
		SetNewMoveDestination(targetCharacter->GetActorLocation());
	}
}

void AHeroPlayerController::AttackGround(FVector location, UAttackComponent* attack)
{
	AHeroCharacter* hero = Cast<AHeroCharacter>(GetPawn());
	if (FVector::Dist(hero->GetActorLocation(), location) < attack->GetRange())
	{
		// Stop moving (HACK)
		SetNewMoveDestination(hero->GetActorLocation());

		FaceLocation(location);
		attack->ActivateAttack(location, NULL);

		if (attack == primedAttack) primedAttack = NULL;
		scheduledAttack = NULL;
	}
	else // Not in range
	{
		scheduledAttack = attack;
		groundTarget = location;
		SetNewMoveDestination(location);
	}
}

void AHeroPlayerController::FaceActor(AActor* actorToFace)
{
	FaceLocation(actorToFace->GetActorLocation());
}

void AHeroPlayerController::FaceLocation(FVector location)
{
	// Rotate attacker towards the defender
	FVector newLookAt = location.operator-=(GetPawn()->GetActorLocation());
	newLookAt.Z = 1; // Make sure character is always upright (attacking on stairs etc.)
	GetPawn()->SetActorRotation(newLookAt.Rotation());
}


void AHeroPlayerController::Pickup(ALoot* loot)
{
	AHeroCharacter* hero = Cast<AHeroCharacter>(GetPawn());
	if (hero->GetDistanceTo(loot) <= pickUpRange)
	{
		SetNewMoveDestination(GetPawn()->GetActorLocation());
		if (AValuable* valuable = dynamic_cast<AValuable*>(loot))
		{
			hero->AddValuable(valuable);
		}
		else
		{
			if (hero->GetInventorySize() < 6)
			{
				hero->AddLoot(loot);
			}
			else
			{
				HA.Toast("Inventory full");
			}
		}
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

void AHeroPlayerController::CancelAction()
{
	bSelectingUnitTarget = false;
	bSelectingGroundTarget = false;

	if (groundTarget != FVector::ZeroVector && !primedAttack)
	{
		scheduledAttack = NULL;
		groundTarget = FVector::ZeroVector;
		SetNewMoveDestination(GetPawn()->GetActorLocation());
	}
	primedAttack = NULL;

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

	if (AGaldrarHUD* hud = dynamic_cast<AGaldrarHUD*>(GetHUD()))
	{
		hud->RemoveAOETemplate();
		hud->RemoveRangeIndicator();
	}
}

void AHeroPlayerController::Spell1(){ if (!bStunned) Spell(0); }
void AHeroPlayerController::Spell2(){ if (!bStunned) Spell(1); }
void AHeroPlayerController::Spell3(){ if (!bStunned) Spell(2); }
void AHeroPlayerController::Spell4(){ if (!bStunned) Spell(3); }

void AHeroPlayerController::Spell(int8 index)
{
	AHeroCharacter* hero = Cast<AHeroCharacter>(GetPawn());

	if (hero->IsSilenced())
	{
		HA.Toast("Silenced");
		return;
	}

	if (!hero->GetSpell(index))
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "No spell in slot " + FString::FromInt(index+1));
		return;
	}
	if (hero->GetSpell(index)->IsOnCoolDown())
	{
		HA.Toast(hero->GetSpell(index)->GetName() + " is not ready");
		return;
	}
	if (hero->GetStats()->mana < hero->GetSpell(index)->GetManaCost())
	{
		HA.Toast("Not enough mana to use " + hero->GetSpell(index)->GetName());
		return;
	}

	switch (hero->GetSpell(index)->GetActivation())
	{
	case EActivation::TARGET_UNIT :
		bSelectingGroundTarget = false;
		bSelectingUnitTarget = true;
		primedAttack = hero->GetSpell(index);
		if (AGaldrarHUD* hud = dynamic_cast<AGaldrarHUD*>(GetHUD()))
		{
			hud->RemoveAOETemplate();
			hud->RemoveRangeIndicator();
			
			hud->CreateRangeIndicator(hero, hero->GetSpell(index)->GetRange(), UGaldrarColor::GetDamageTypeColor(hero->GetSpell(index)->GetDamageType()));
		}
		break;
	
	case EActivation::TARGET_GROUND :
		bSelectingGroundTarget = true;
		bSelectingUnitTarget = false;
		primedAttack = hero->GetSpell(index);
		if (hero->GetSpell(index)->GetSpellTarget() == ESpellTarget::CIRCLE)
		{
			if (AGaldrarHUD* hud = dynamic_cast<AGaldrarHUD*>(GetHUD()))
			{
				hud->RemoveAOETemplate();
				hud->RemoveRangeIndicator();
				
				hud->CreateRangeIndicator(hero, hero->GetSpell(index)->GetRange(), UGaldrarColor::GetDamageTypeColor(hero->GetSpell(index)->GetDamageType()));
				
				hud->CreateAOECircle(hero, hero->GetSpell(index)->GetRadius(), 
					UGaldrarColor::GetDamageTypeColor(hero->GetSpell(index)->GetDamageType()));
			}
		}
		else if (hero->GetSpell(index)->GetSpellTarget() == ESpellTarget::CONE)
		{
			if (AGaldrarHUD* hud = dynamic_cast<AGaldrarHUD*>(GetHUD()))
			{
				hud->RemoveAOETemplate();
				hud->RemoveRangeIndicator();
				
				hud->CreateRangeIndicator(hero, hero->GetSpell(index)->GetRange(), UGaldrarColor::GetDamageTypeColor(hero->GetSpell(index)->GetDamageType()));
				
				hud->CreateAOECone(hero, hero->GetSpell(index)->GetRange(), hero->GetSpell(index)->GetRadius(),
					UGaldrarColor::GetDamageTypeColor(hero->GetSpell(index)->GetDamageType()));
			}
		}
		break;

	case EActivation::PASSIVE :
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Passive");
		break;

	case EActivation::ATTACK_MODIFIER :
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Attack Modifier");
		groundTarget = FVector::ZeroVector;
		break;

	case EActivation::SELF :
		hero->GetSpell(index)->ActivateAttack(FVector::ZeroVector, hero);
		groundTarget = FVector::ZeroVector;
		break;
	}
}

void AHeroPlayerController::Inventory1(){ Inventory(0); }
void AHeroPlayerController::Inventory2(){ Inventory(1); }
void AHeroPlayerController::Inventory3(){ Inventory(2); }
void AHeroPlayerController::Inventory4(){ Inventory(3); }
void AHeroPlayerController::Inventory5(){ Inventory(4); }
void AHeroPlayerController::Inventory6(){ Inventory(5); }

void AHeroPlayerController::Inventory(int8 index)
{
	AHeroCharacter* hero = Cast<AHeroCharacter>(GetPawn());
	if (hero->GetInventory(index))
	{
		ItemHandler::ActivateItem(hero->GetInventory(index), hero, hero);
	}
}

void AHeroPlayerController::UseBloodVial()
{
	AHeroCharacter* hero = Cast<AHeroCharacter>(GetPawn());
	hero->UseBloodVial();
}
