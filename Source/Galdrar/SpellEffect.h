// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "BaseCharacter.h"
#include "Attack.h"
#include "SpellEffect.generated.h"

UCLASS()
class GALDRAR_API ASpellEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpellEffect();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void Initialize(ABaseCharacter* caster, Attack* attack)
	{
		this->caster = caster;
		this->attack = attack;
	}

	TSubclassOf<class ASpellEffect> GasCloudBluePrintReference;

	ABaseCharacter* caster;
	Attack* attack;
};
