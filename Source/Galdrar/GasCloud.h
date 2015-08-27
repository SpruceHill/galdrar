// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "BaseSpell.h"
#include "SpellEffect.h"
#include "GasCloud.generated.h"

/**
 * 
 */
UCLASS()
class GALDRAR_API UGasCloud : public UBaseSpell
{
	GENERATED_BODY()
public:
	UGasCloud();
	
	void ActivateAttack(FVector location, ABaseCharacter* target) override;

private:
	//TSubclassOf<class ASpellEffect> blueprintReference;

};
