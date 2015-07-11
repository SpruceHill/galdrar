// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "SpellHandler.h"
#include "ProjectileFactory.h"

// Target unit
void SpellHandler::ActivateSpell(Spell* spell, ABaseCharacter* caster, ABaseCharacter* target)
{

}
// Target ground
void SpellHandler::ActivateSpell(Spell* spell, UWorld* world, const FVector &location, ABaseCharacter* caster)
{
	if (spell->IsProjectile())
	{
		UProjectileFactory::SpawnAttackEffect(world, caster, location, spell);
	}
}
// Self
void SpellHandler::ActivateSpell(Spell* spell, ABaseCharacter* caster)
{

}