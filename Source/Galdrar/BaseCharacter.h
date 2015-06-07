 // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

UCLASS(abstract)
class GALDRAR_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties


	// Called when the game starts or when spawned
	//virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaSeconds) override { Super::Tick(DeltaSeconds); }

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	

/*private:
	unsigned int maxHealth;
	unsigned int health;
	double armour;
	double frostResistance;
	double fireResistance;
	double shockResistance;
	// List effects
	// Array / variables spells*/
};