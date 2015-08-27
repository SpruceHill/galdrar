// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "BaseSpell.h"
#include "Teleport.generated.h"

/**
 * 
 */
UCLASS()
class GALDRAR_API UTeleport : public UBaseSpell
{
	GENERATED_BODY()
public:
	UTeleport();

	void ActivateAttack(FVector location, ABaseCharacter* target) override;
	
};
