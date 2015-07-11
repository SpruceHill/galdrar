// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "Spell.h"
#include "BaseCharacter.h"

/**
 * 
 */
class GALDRAR_API SpellHandler
{
public:
	// Target unit
	static void ActivateSpell(Spell* spell, ABaseCharacter* caster, ABaseCharacter* target);
	// Target ground
	static void ActivateSpell(Spell* spell, UWorld* world, const FVector &location, ABaseCharacter* caster);
	// Self
	static void ActivateSpell(Spell* spell, ABaseCharacter* caster);
};
