// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "Effect.h"

/**
 * 
 */
class GALDRAR_API HealEffect : public Effect
{
public:
	HealEffect();
	HealEffect(UCharacterStatsComponent* stats);
	~HealEffect();

	virtual void Tick(float delta) override;
};
