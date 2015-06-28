// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "Attack.h"
#include "EffectType.h"
#include "DamageType.h"
#include <list>

class GALDRAR_API Spell : Attack
{
public:
	enum SpellType { TARGET, PASSIVE, AOE };

	virtual void Activate();

	SpellType GetSpellType() { return spellType; }
	float GetDamage(){ return damage; }
	float GetManaCost(){ return manaCost; }
	float GetCooldown(){ return cooldown; }
	std::list < EffectType* > GetEffectTypes(){ return effectTypes; }
	DamageType GetDamageType(){ return damageType; }

	Spell();
	~Spell();

private:
	SpellType spellType;
	float damage;
	float manaCost;
	float cooldown;
	float time;
	std::list < EffectType* > effectTypes;
	DamageType damageType;
};
