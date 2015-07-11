// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "SpellHandler.h"
#include "ProjectileFactory.h"

// Target unit
void SpellHandler::ActivateSpell(Attack* attack, ABaseCharacter* caster, ABaseCharacter* target)
{
	Spell* spell = (Spell*)attack;
	switch (spell->GetSpellType())
	{
	case Spell::SpellType::HEAL: 
		target->Heal(spell->GetDamage());
		break;
	default: return;
	}
}
// Target ground
void SpellHandler::ActivateSpell(Attack* attack, UWorld* world, FVector location, ABaseCharacter* caster)
{
	Spell* spell = (Spell*)attack;
	switch (spell->GetSpellType())
	{
	case Spell::SpellType::DRAGONS_BREATH: 
		UProjectileFactory::SpawnAttackEffect(world, caster, location, spell); 
		break;
	case Spell::SpellType::JAVELIN: 
		UProjectileFactory::SpawnAttackEffect(world, caster, location, spell);
		caster->Heal(2);
		break;
	case Spell::SpellType::GAS_CLOUD: 
		UProjectileFactory::SpawnAttackEffect(world, caster, location, spell); 
		break;
	case Spell::SpellType::LIGHNING_BOLT: 
		UProjectileFactory::SpawnAttackEffect(world, caster, location, spell); 
		break;
	default: return;
	}
}
// Self
void SpellHandler::ActivateSpell(Attack* attack, ABaseCharacter* caster)
{

}