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

Attack::Attack()
{
	// Setting defaults, should never be called.
	damage = 0;
	damageType = DamageType::PHYSICAL;
	critMultiplier = 1.f;
	range = 0.f;
	attackSpeed = 1.f;
	name = "No name";
	cooldown = 1.f;
	time = 0.f;

	bProjectile = false;
	bProjectilePenetration = false;
	projectileWidth = 0.f;
	projectileSpeed = 0.f;
}

void Attack::Activate()
{
	time = cooldown;
}

void Attack::Tick(float deltaSeconds)
{
	if (time > 0.f)
	{
		time -= deltaSeconds;
	}
}

Attack::~Attack(){};
