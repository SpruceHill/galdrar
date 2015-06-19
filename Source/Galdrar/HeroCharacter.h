// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BaseCharacter.h"
#include "Loot.h"
#include "Valuable.h"
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

	void AddValuable(AValuable* valuable) 
	{ 
		lootValue += valuable->GetValue();
	}

	void AddLoot(ALoot* loot) {
		inventory.Add(loot);
	}
protected:
	int32 lootValue;
	TArray<ALoot*> inventory;

};
