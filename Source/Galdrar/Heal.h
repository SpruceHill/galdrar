// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "BaseSpell.h"
#include "SpellEffect.h"
#include "Heal.generated.h"

/**
 * 
 */
UCLASS()
class GALDRAR_API UHeal : public UBaseSpell
{
	GENERATED_BODY()
public:
	UHeal();

	void ActivateAttack(FVector location, ABaseCharacter* target) override;

private:
	TSubclassOf<class ASpellEffect> blueprintReference;

	
	
	
};
