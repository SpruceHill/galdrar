// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "CharacterStatsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GALDRAR_API UCharacterStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterStatsComponent();

	// Called when the game starts
	virtual void InitializeComponent() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	/* COMBAT STATS */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
	float defaultMaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
	float maxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
	float health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
	float defaultMaxMana;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
	float maxMana;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
	float mana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
	float defaultManaReg;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
	float manaReg;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
	float rage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
	float rageGenerationMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
	float rageDegenerationRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
	float defaultArmour;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
	float armour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
	float defaultFrostRes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
	float frostResistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
	float defaultFireRes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
	float fireResistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
	float defaultShockRes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
	float shockResistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
	float defaultPoisonRes;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
	float poisonResistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
	float defaultDamageMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
	float damageMultiplier;

	/* MOVEMENT STATS */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
	float defaultRotationRate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
	float rotationRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
	float defaultMovementSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
	float movementSpeed;
};
