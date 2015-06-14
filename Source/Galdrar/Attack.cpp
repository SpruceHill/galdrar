// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "Attack.h"
#include "Effect.h"
#include "DamageType.h"
#include <list>

Attack::Attack(FString name, float damage, DamageType type, float critMultiplier, float range, float attackSpeed)
{//, std::list < Effect* > effects
	this->name = name;
	this->damage = damage;
	//this->effects = effects;
	this->attackType = type;
	this->critMultiplier = critMultiplier;
	this->range = range;
	this->attackSpeed = attackSpeed;
}