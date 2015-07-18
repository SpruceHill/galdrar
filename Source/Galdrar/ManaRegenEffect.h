// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "Effect.h"

/**
 * 
 */
class GALDRAR_API ManaRegenEffect : public Effect
{
public:
	ManaRegenEffect();
	ManaRegenEffect(CharacterStats* stats);
	~ManaRegenEffect();

	virtual void Tick(float delta) override;
};
