// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "Attack.h"
#include "Effect.h"
#include "DamageType.h"
#include <list>

Attack::Attack(FString name, float damage, DamageType type, float critMultiplier, float range, float attackSpeed, const std::list < EffectType > effectTypes)
{
	this->name = name;
	this->damage = damage;
	this->effectTypes = effectTypes;
	this->damageType = type;
	this->critMultiplier = critMultiplier;
	this->range = range;
	this->attackSpeed = attackSpeed;
}