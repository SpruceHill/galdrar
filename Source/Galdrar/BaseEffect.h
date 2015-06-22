// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "DamageType.h"
#include "CharacterStats.h"
#include "BaseEffect.generated.h"

/**
 * 
 */
UCLASS(abstract)
class GALDRAR_API ABaseEffect : public AActor
{
	GENERATED_BODY()
	
public:
	//UFUNCTION(BlueprintCallable, Category = Effect)
	void Init(CharacterStats* stats);
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

};
