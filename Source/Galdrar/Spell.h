// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "Attack.h"
#include "EffectType.h"
#include "DamageType.h"
#include <list>

class GALDRAR_API Spell : public Attack
{
public:
	enum SpellType { TARGET, PASSIVE, AOE };

	virtual void Activate();

	SpellType GetSpellType() { return spellType; }
	float GetManaCost(){ return manaCost; }

	Spell();
	~Spell();

protected:
	SpellType spellType;
	float manaCost;
};
