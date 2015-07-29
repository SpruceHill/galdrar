// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "BaseCharacter.h"
#include "Loot.h"
#include "Valuable.h"
#include "HUDAdapter.h"
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

	UFUNCTION(BlueprintCallable, Category = Input)
	void Spell1();
	UFUNCTION(BlueprintCallable, Category = Input)
	void Spell2();
	UFUNCTION(BlueprintCallable, Category = Input)
	void Spell3();
	UFUNCTION(BlueprintCallable, Category = Input)
	void Spell4();

	UFUNCTION(BlueprintCallable, Category = Input)
	void Inventory1();
	UFUNCTION(BlueprintCallable, Category = Input)
	void Inventory2();
	UFUNCTION(BlueprintCallable, Category = Input)
	void Inventory3();
	UFUNCTION(BlueprintCallable, Category = Input)
	void Inventory4();
	UFUNCTION(BlueprintCallable, Category = Input)
	void Inventory5();
	UFUNCTION(BlueprintCallable, Category = Input)
	void Inventory6();

	UFUNCTION(BlueprintCallable, Category = Input)
	void UseBloodVial();

private:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	const float zoomStepLength = 100.f;
	const float zoomSpeed = 20.f;
	const float zoomMin = 500.f;
	const float zoomMax = 1000.f;
	float targetZoom;
	bool bShouldZoom;
	bool bSelectingUnitTarget;
	bool bSelectingGroundTarget;
	float pickUpRange = 120.f;
	ABaseCharacter* targetCharacter;
	FVector groundTarget;
	ALoot* targetLoot;
	HUDAdapter HA;
	Attack* scheduledAttack;
	Attack* primedAttack;
	bool bStunned;

	virtual void BeginPlay() override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	void MoveToMouseCursor();

	void SetNewMoveDestination(const FVector DestLocation);

	void UpdateCursorOverState();

	// Input handlers
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	void Zoom(float delta);
	void ZoomIn(){ Zoom(-zoomStepLength); }
	void ZoomOut(){ Zoom(zoomStepLength); }

	void Spell(int8 index);

	void Inventory(int8 index);

	void CancelAction();
	
	// Helpers
	void AttackEnemy(ABaseCharacter* character, Attack* attack);
	void AttackGround(FVector location, Attack* attack);
	void Pickup(ALoot* loot);

	void FaceActor(AActor* actorToFace);
	void FaceLocation(FVector location);

};
