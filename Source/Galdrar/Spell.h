// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "Attack.h"
#include <list>

class GALDRAR_API Spell : public Attack
{
public:
	enum SpellType { DRAGONS_BREATH, GAS_CLOUD, LIGHNING_BOLT, JAVELIN, HEAL, TELEPORT };
	enum SpellTarget { UNIT, CIRCLE, CONE, AURA };
	enum Activation { TARGET_UNIT, TARGET_GROUND, PASSIVE, ATTACK_MODIFIER, SELF };

	SpellType GetSpellType() { return spellType; }
	SpellTarget GetSpellTarget() { return spellTarget; }
	Activation GetActivation() { return activation; }
	float GetManaCost(){ return manaCost; }
	float GetRadius(){ return radius; }

	Spell();
	~Spell();

protected:
	SpellType spellType;
	SpellTarget spellTarget;
	Activation activation;
	float manaCost;
	float radius;
};
