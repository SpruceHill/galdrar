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
		case DamageType::FIRE: return GetFireColor();
		case DamageType::FROST: return GetFrostColor();
		case DamageType::SHOCK: return GetShockColor();
		case DamageType::POISON: return GetPoisonColor();
		case DamageType::PHYSICAL: return GetPhysicalColor();
		case DamageType::TRUE: return GetTrueDamageColor();
		default: return FColor::Black;
		}
	}

	/*
	*	DAMAGE TYPES
	*/
	static FColor GetFireColor()
	{
		return FColor::FromHex("FF5300FF");
	}
	static FColor GetFrostColor()
	{
		return FColor::FromHex("6BBEFFFF");
	}
	static FColor GetShockColor()
	{
		return FColor::FromHex("B410FFFF");
	}
	static FColor GetPoisonColor()
	{
		return FColor::FromHex("009866FF");
	}
	static FColor GetPhysicalColor()
	{
		return FColor::White;
	}
	static FColor GetTrueDamageColor()
	{
		return FColor::White;
	}

	// GOLD
	static FColor GetGoldColor()
	{
		return FColor::FromHex("DAA520FF");
	}

	static FColor GetHealColor()
	{
		return FColor::Green;
	}
};
