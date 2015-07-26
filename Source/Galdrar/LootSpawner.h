// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Loot.h"
#include "LootSpawner.generated.h"

/**
 * 
 */
UCLASS()
class GALDRAR_API ULootSpawner : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = Loot)
	static void SpawnLootAtActor(AActor* actor, TSubclassOf<ALoot> loot);
};
