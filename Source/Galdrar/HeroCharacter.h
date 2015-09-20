// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseCharacter.h"
#include "Loot.h"
#include "Valuable.h"
#include "GaldrarColor.h"
#include "HUDAdapter.h"
#include "BloodVialComponent.h"
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

	UFUNCTION(BlueprintCallable, Category = HeroCharacter)
	void InitializeHero(
			TSubclassOf<UBaseWeapon> MainWeapon,
			TSubclassOf<UBaseSpell> NewSpell1,
			TSubclassOf<UBaseSpell> NewSpell2,
			TSubclassOf<UBaseSpell> NewSpell3,
			TSubclassOf<UBaseSpell> NewSpell4,
			TSubclassOf<UBaseTrait> NewTrait1,
			TSubclassOf<UBaseTrait> NewTrait2,
			TSubclassOf<UBloodVialComponent> NewBloodVial
			);

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	void SetCameraBoom(float length)  { CameraBoom->TargetArmLength = length; }

	void Zoom(float delta);

	UFUNCTION(BlueprintCallable, Category = Loot)
	void AddValuable(AValuable* valuable);

	UFUNCTION(BlueprintCallable, Category = Loot)
	void RemoveLootValue(int32 amount);

	UFUNCTION(BlueprintCallable, Category = Loot)
	int32 GetLootValue();

	void AddLoot(ALoot* loot)
	{
		if (!inventorySlot1)
		{
			inventorySlot1 = loot; 
		}
		else if (!inventorySlot2)
		{
			inventorySlot2 = loot;
		}
		else if (!inventorySlot3)
		{
			inventorySlot3 = loot;
		}
		else if (!inventorySlot4)
		{
			inventorySlot4 = loot;
		}
		else if (!inventorySlot5)
		{
			inventorySlot5 = loot;
		}
		else if (!inventorySlot6)
		{
			inventorySlot6 = loot;
		}
		stats->movementSpeed -= loot->GetWeight();
		loot->OnPickup();
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
		if (inventorySlot1 == loot)
		{
			inventorySlot1->MarkPendingKill();
			inventorySlot1 = NULL;
		}
		else if (inventorySlot2 == loot)
		{
			inventorySlot2->MarkPendingKill();
			inventorySlot2 = NULL;
		}
		else if (inventorySlot3 == loot)
		{
			inventorySlot3->MarkPendingKill();
			inventorySlot3 = NULL;
		}
		else if (inventorySlot4 == loot)
		{
			inventorySlot4->MarkPendingKill();
			inventorySlot4 = NULL;
		}
		else if (inventorySlot5 == loot)
		{
			inventorySlot5->MarkPendingKill();
			inventorySlot5 = NULL;
		}
		else if (inventorySlot6 == loot)
		{
			inventorySlot6->MarkPendingKill();
			inventorySlot6 = NULL;
		}
		stats->movementSpeed += loot->GetWeight();
	}

	UFUNCTION(BlueprintCallable, Category = Loot)
	ALoot* GetInventory(int32 index);

	void UseBloodVial()
	{
		bloodVialComponent->Use();
	}

	UFUNCTION(BlueprintCallable, Category = BloodVial)
	UBloodVialComponent* GetBloodVial();

	UFUNCTION(BlueprintCallable, Category = BloodVial)
	int32 GetBloodVialID();
	UFUNCTION(BlueprintCallable, Category = BloodVial)
	int32 GetBloodVialMaxCharges();
	UFUNCTION(BlueprintCallable, Category = BloodVial)
	int32 GetBloodVialCharges();
	UFUNCTION(BlueprintCallable, Category = BloodVial)
	void AddBloodVialCharges(int32 nbrOfCharges);

protected:
	int32 lootValue;
	ALoot* inventorySlot1;
	ALoot* inventorySlot2;
	ALoot* inventorySlot3;
	ALoot* inventorySlot4;
	ALoot* inventorySlot5;
	ALoot* inventorySlot6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HeroCharacter)
	UBloodVialComponent* bloodVialComponent;
};
