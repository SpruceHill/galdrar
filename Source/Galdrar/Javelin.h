// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "BaseSpell.h"
#include "Javelin.generated.h"

/**
 * 
 */
UCLASS()
class GALDRAR_API UJavelin : public UBaseSpell
{
	GENERATED_BODY()
	
public:
	UJavelin();

	void ActivateAttack(FVector location, ABaseCharacter* target) override;

private:
	TSubclassOf<class ASpellEffect> blueprintReference;

	
	
};
