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
		case DamageType::FIRE: return FColor::FromHex("FF5300FF");
		case DamageType::FROST: return FColor::FromHex("6BBEFFFF");
		case DamageType::SHOCK: return FColor::FromHex("B410FFFF");
		case DamageType::POISON: return FColor::FromHex("00D10AFF");
		case DamageType::PHYSICAL: return FColor::White;
		default: return FColor::Black;
		}
	}
		
};
