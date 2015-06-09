// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "Attack.h"
#include "Effect.h"
#include "DamageType.h"
#include <list>

Attack::Attack(float damage, DamageType type, float critPercentage)
{//, std::list < Effect* > effects
	this->damage = damage;
	//this->effects = effects;
	this->attackType = type;
	this->critPercentage = critPercentage;
}