// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "BaseSpell.h"
#include "LightningBolt.generated.h"

/**
 * 
 */
UCLASS()
class GALDRAR_API ULightningBolt : public UBaseSpell
{
	GENERATED_BODY()

public:
	ULightningBolt();

	void ActivateAttack(FVector location, ABaseCharacter* target) override;

private:
	TSubclassOf<class ASpellEffect> blueprintReference;
	
	
	
};
