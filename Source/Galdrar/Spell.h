// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "Attack.h"
#include "Effect.h"
#include "DamageType.h"
#include <list>

class GALDRAR_API Spell : Attack
{
public:

	Spell(float damage, std::list < Effect* > effects, DamageType type, float manaCost);
	~Spell();
};
