// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseCharacter.h"
#include "Loot.h"
#include "Valuable.h"
#include "GaldrarColor.h"
#include "HUDAdapter.h"
#include "HeroCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GALDRAR_API AHeroCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
	// Top down camera
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	// Camera boom positioning the camera above the character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	
public:
	AHeroCharacter(const FObjectInitializer& ObjectInitializer);

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	void SetCameraBoom(float length)  { CameraBoom->TargetArmLength = length; }

	void Zoom(float delta);

	UFUNCTION(BlueprintCallable, Category = Loot)
	void AddValuable(AValuable* valuable);

	UFUNCTION(BlueprintCallable, Category = Loot)
	int32 GetLootValue();

	void AddLoot(ALoot* loot)
	{
		bool placed = false;
		//inventory.Add(loot);
		if (!inventorySlot1 && !placed)
		{
			inventorySlot1 = loot; 
			placed = true;
		}
		if (!inventorySlot2 && !placed)
		{
			inventorySlot2 = loot;
			placed = true;
		}
		if (!inventorySlot3 && !placed)
		{
			placed = true;
			inventorySlot3 = loot;
		}
		if (!inventorySlot4 && !placed)
		{
			placed = true;
			inventorySlot4 = loot;
		}
		if (!inventorySlot5 && !placed)
		{
			placed = true;
			inventorySlot5 = loot;
		}
		if (!inventorySlot6 && !placed)
		{
			placed = true;
			inventorySlot6 = loot;
		}
		loot->SetActorHiddenInGame(true);
		loot->SetActorEnableCollision(false);
	}

	int32 GetInventorySize()
	{
		int32 num = 0;
		if (inventorySlot1) num++;
		if (inventorySlot2) num++;
		if (inventorySlot3) num++;
		if (inventorySlot4) num++;
		if (inventorySlot5) num++;
		if (inventorySlot6) num++;
		return num;
	}

	void RemoveItem(ALoot* loot)
	{
		if (inventorySlot1 == loot) inventorySlot1->Destroy();
		else if (inventorySlot2 == loot) inventorySlot1->Destroy();
		else if (inventorySlot3 == loot) inventorySlot1->Destroy();
		else if (inventorySlot4 == loot) inventorySlot1->Destroy();
		else if (inventorySlot5 == loot) inventorySlot1->Destroy();
		else if (inventorySlot6 == loot) inventorySlot1->Destroy();
	}

	/*
	*	SPELL GETTERS
	*/
	UFUNCTION(BlueprintCallable, Category = Spells)
	int32 GetSpellIdAtIndex(int32 index);

	UFUNCTION(BlueprintCallable, Category = Spells)
	float GetSpellCooldownAtIndex(int32 index);
	
	UFUNCTION(BlueprintCallable, Category = Spells)
	float GetSpellTimeAtIndex(int32 index);

	UFUNCTION(BlueprintCallable, Category = Spells)
	FString GetSpellNameAtIndex(int32 index);

	UFUNCTION(BlueprintCallable, Category = Spells)
	FString GetSpellDescAtIndex(int32 index);

	UFUNCTION(BlueprintCallable, Category = Loot)
	ALoot* GetInventory(int32 index);

protected:
	int32 lootValue;
	ALoot* inventorySlot1;
	ALoot* inventorySlot2;
	ALoot* inventorySlot3;
	ALoot* inventorySlot4;
	ALoot* inventorySlot5;
	ALoot* inventorySlot6;
};
