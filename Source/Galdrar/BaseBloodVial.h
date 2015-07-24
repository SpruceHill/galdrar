// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "CharacterStats.h"

/**
 * 
 */
class GALDRAR_API BaseBloodVial
{
public:
	BaseBloodVial(CharacterStats* stats);
	~BaseBloodVial();

	virtual void Activate();

	int32 ID;
};
