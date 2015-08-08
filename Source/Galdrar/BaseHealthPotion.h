// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "Loot.h"
#include "BaseHealthPotion.generated.h"

/**
 * 
 */
UCLASS()
class GALDRAR_API ABaseHealthPotion : public ALoot
{
	GENERATED_BODY()
public:
	void Activate(UCharacterStatsComponent* ownerStats, UCharacterStatsComponent* targetStats) override;
	
	
	
};
