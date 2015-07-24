// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "CharacterStats.h"

/**
 * 
 */
class GALDRAR_API BaseBloodVial
{
public:
	BaseBloodVial();
	BaseBloodVial(CharacterStats* stats);
	~BaseBloodVial();

	virtual void Activate();

	int32 GetMaxCharges() { return maxCharges; }
	int32 GetCharges() { return charges; }
	int32 GetID() { return ID; };

protected:
	int32 ID;
	
	// Number of charges that can be spent
	int32 maxCharges;
	// Current amount
	int32 charges;
	// Cost of using the vial. Should be a multiple of charges
	int32 cost;

	CharacterStats* stats;
};
