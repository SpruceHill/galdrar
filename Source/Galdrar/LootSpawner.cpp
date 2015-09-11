// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "LootSpawner.h"

void ULootSpawner::SpawnLootAtActor(AActor* actor, TSubclassOf<ALoot> loot)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride;
	actor->GetWorld()->SpawnActor<ALoot>(loot, actor->GetActorLocation(), FRotator(0, 0, 0), SpawnParameters);
}


