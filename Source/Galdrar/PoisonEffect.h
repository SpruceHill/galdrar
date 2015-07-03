// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "Effect.h"

/**
 * 
 */
class GALDRAR_API PoisonEffect : public Effect
{
public:
	PoisonEffect();
	PoisonEffect(CharacterStats* stats);

	virtual void Tick(float delta) override;
};
