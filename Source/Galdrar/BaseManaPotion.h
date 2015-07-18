// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "Loot.h"
#include "BaseManaPotion.generated.h"

/**
 * 
 */
UCLASS()
class GALDRAR_API ABaseManaPotion : public ALoot
{
	GENERATED_BODY()
public:
	void Activate(CharacterStats* ownerStats, CharacterStats* targetStats) override;
	
};
