// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "DamageType.h"
/**
 * 
 */
class GALDRAR_API GaldrarColor
{
public:
	static FColor GetDamageTypeColor(DamageType type)
	{
		switch (type)
		{
		case DamageType::FIRE: return FColor::Red;
		case DamageType::FROST: return FColor::Blue;
		case DamageType::SHOCK: return FColor::Magenta;
		case DamageType::PHYSICAL: return FColor::White;
		default: return FColor::Black;
		}
	}
		
};
