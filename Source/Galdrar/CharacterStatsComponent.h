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
	UPROPERTY(BlueprintReadWrite, Category = CharacterStats)
	float defaultMaxHealth;
	UPROPERTY(BlueprintReadWrite, Category = CharacterStats)
	float maxHealth;
	UPROPERTY(BlueprintReadWrite, Category = CharacterStats)
	float health;

	UPROPERTY(BlueprintReadWrite, Category = CharacterStats)
	float defaultMaxMana;
	UPROPERTY(BlueprintReadWrite, Category = CharacterStats)
	float maxMana;
	UPROPERTY(BlueprintReadWrite, Category = CharacterStats)
	float mana;

	UPROPERTY(BlueprintReadWrite, Category = CharacterStats)
	float defaultManaReg;
	UPROPERTY(BlueprintReadWrite, Category = CharacterStats)
	float manaReg;

	UPROPERTY(BlueprintReadWrite, Category = CharacterStats)
	float defaultArmour;
	UPROPERTY(BlueprintReadWrite, Category = CharacterStats)
	float armour;

	UPROPERTY(BlueprintReadWrite, Category = CharacterStats)
	float defaultFrostRes;
	UPROPERTY(BlueprintReadWrite, Category = CharacterStats)
	float frostResistance;

	UPROPERTY(BlueprintReadWrite, Category = CharacterStats)
	float defaultFireRes;
	UPROPERTY(BlueprintReadWrite, Category = CharacterStats)
	float fireResistance;

	UPROPERTY(BlueprintReadWrite, Category = CharacterStats)
	float defaultShockRes;
	UPROPERTY(BlueprintReadWrite, Category = CharacterStats)
	float shockResistance;

	UPROPERTY(BlueprintReadWrite, Category = CharacterStats)
	float defaultPoisonRes;
	UPROPERTY(BlueprintReadWrite, Category = CharacterStats)
	float poisonResistance;

	UPROPERTY(BlueprintReadWrite, Category = CharacterStats)
	float defaultDamageMultiplier;
	UPROPERTY(BlueprintReadWrite, Category = CharacterStats)
	float damageMultiplier;

	/* MOVEMENT STATS */
	UPROPERTY(BlueprintReadWrite, Category = CharacterStats)
	float defaultRotationRate;
	UPROPERTY(BlueprintReadWrite, Category = CharacterStats)
	float rotationRate;

	UPROPERTY(BlueprintReadWrite, Category = CharacterStats)
	float defaultMovementSpeed;
	UPROPERTY(BlueprintReadWrite, Category = CharacterStats)
	float movementSpeed;
};
