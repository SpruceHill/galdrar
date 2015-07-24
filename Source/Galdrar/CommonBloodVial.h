// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "BaseBloodVial.h"

/**
 * 
 */
class GALDRAR_API CommonBloodVial : public BaseBloodVial
{
public:
	CommonBloodVial();
	CommonBloodVial(CharacterStats* stats);
	~CommonBloodVial();

	void Activate() override;
};
