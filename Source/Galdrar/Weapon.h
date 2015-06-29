// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "Attack.h"

/**
 * 
 */
class GALDRAR_API Weapon : public Attack
{
public:
	Weapon();
	~Weapon();

	float GetWeight(){ return weight; }
	int32 GetKills(){ return kills; }
	bool IsTwoHanded(){ return twoHanded; }

protected:
	float weight;
	int32 kills;
	bool twoHanded;
};
