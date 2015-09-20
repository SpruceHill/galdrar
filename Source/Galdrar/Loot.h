// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "BaseInteractable.h"
#include "Loot.generated.h"

/*
* This class represents everything that can be picked up in the world.
*/
UCLASS(abstract)
class GALDRAR_API ALoot : public ABaseInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALoot();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void Activate(UCharacterStatsComponent* ownerStats, UCharacterStatsComponent* targetStats);

	// Implement in blueprint
	UFUNCTION(BlueprintImplementableEvent, Category = Loot)
	void OnPickup();

	UFUNCTION(BlueprintCallable, Category = Loot)
	int32 GetID();
	UFUNCTION(BlueprintCallable, Category = Loot)
	bool IsStackable();
	UFUNCTION(BlueprintCallable, Category = Loot)
	bool IsActivatable();
	UFUNCTION(BlueprintCallable, Category = Loot)
	float GetWeight();

protected:
	UFUNCTION(BlueprintCallable, Category = Loot)
	void Disable();

	UPROPERTY(BlueprintReadWrite, Category = Loot)
	int32 ID;
	UPROPERTY(BlueprintReadWrite, Category = Loot)
	bool bStackable;
	UPROPERTY(BlueprintReadWrite, Category = Loot)
	bool bActivatable;
	UPROPERTY(BlueprintReadWrite, Category = Loot)
	float time;
	UPROPERTY(BlueprintReadWrite, Category = Loot)
	float cooldown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Armor, meta = (AllowPrivateAccess = "true"))
	float weight;
};
