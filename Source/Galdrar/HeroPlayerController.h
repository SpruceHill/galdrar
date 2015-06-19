// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "BaseCharacter.h"
#include "Loot.h"
#include "Valuable.h"
#include "HeroPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GALDRAR_API AHeroPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AHeroPlayerController(const FObjectInitializer& ObjectInitializer);

private:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;
	const float zoomStepLength = 100.f;
	const float zoomSpeed = 20.f;
	const float zoomMin = 500.f;
	const float zoomMax = 1200.f;
	float targetZoom;
	bool bShouldZoom;

	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	void MoveToMouseCursor();

	void SetNewMoveDestination(const FVector DestLocation);

	// Input handlers for SetDestination action
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	void Zoom(float delta);
	void ZoomIn(){ Zoom(-zoomStepLength); }
	void ZoomOut(){ Zoom(zoomStepLength); }

	void Attack(ABaseCharacter* character);
	void Pickup(ALoot* loot);

	ABaseCharacter* targetCharacter;
	ALoot* targetLoot;

	float pickUpRange = 120.f;
};
