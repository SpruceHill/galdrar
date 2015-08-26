// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "BaseSpell.h"

TEnumAsByte<ESpellTarget::Type> UBaseSpell::GetSpellTarget()
{
	return spellTarget;
}

TEnumAsByte<EActivation::Type> UBaseSpell::GetActivation()
{
	return activation;
}

float UBaseSpell::GetManaCost()
{ 
	return manaCost; 
}
float UBaseSpell::GetRadius()
{
	return radius;
}


