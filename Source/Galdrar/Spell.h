// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "Attack.h"
#include "EffectType.h"
#include "DamageType.h"
#include <list>

class GALDRAR_API Spell : public Attack
{
public:
	enum SpellTarget { UNIT, RADIUS, CONE, AURA };
	enum Activation { TARGET_UNIT, TARGET_GROUND, PASSIVE, ATTACK_MODIFIER, SELF };
	virtual void Activate();

	SpellTarget GetSpellTarget() { return spellTarget; }
	Activation GetActivation() { return activation; }
	float GetManaCost(){ return manaCost; }

	Spell();
	~Spell();

protected:
	SpellTarget spellTarget;
	Activation activation;
	float manaCost;
	float radius;
};
