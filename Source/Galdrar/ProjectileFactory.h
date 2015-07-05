// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "BaseCharacter.h"
#include "Attack.h"
#include "ProjectileFactory.generated.h"

/**
 * 
 */
UCLASS()
class GALDRAR_API UProjectileFactory : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	void SpawnProjectile(ABaseCharacter* attacker, FVector targetLocation, Attack* attack);
};
