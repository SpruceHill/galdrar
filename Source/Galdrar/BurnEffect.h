// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "Effect.h"

/**
 * 
 */
class GALDRAR_API BurnEffect : public Effect
{
public:
	BurnEffect();
	BurnEffect(CharacterStats* stats);
	
	virtual bool Tick(float delta) override;
};
