// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "GaldrarColor.h"

FColor UGaldrarColor::GetDamageTypeColor(EGaldrarDamageType type)
{
	switch (type)
	{
	case EGaldrarDamageType::FIRE: return GetFireColor();
	case EGaldrarDamageType::FROST: return GetFrostColor();
	case EGaldrarDamageType::SHOCK: return GetShockColor();
	case EGaldrarDamageType::POISON: return GetPoisonColor();
	case EGaldrarDamageType::PHYSICAL: return GetPhysicalColor();
	default: return FColor::Black;
	}
}

FColor UGaldrarColor::GetLevelColor(int32 level)
{
	switch (level)
	{
	case 1: return FColor::White;
	case 2: return FColor::FromHex("FFDE00FF");
	case 3: return FColor::FromHex("FF6A00FF");
	case 4: return FColor::FromHex("FF0600FF");
	case 5: return FColor::FromHex("8800C1FF");
	default: return FColor::Black;
	}
}

FColor UGaldrarColor::GetFireColor()
{
	return FColor::FromHex("FF5300FF");
}
FColor UGaldrarColor::GetFrostColor()
{
	return FColor::FromHex("6BBEFFFF");
}
FColor UGaldrarColor::GetShockColor()
{
	return FColor::FromHex("B410FFFF");
}
FColor UGaldrarColor::GetPoisonColor()
{
	return FColor::FromHex("009866FF");
}
FColor UGaldrarColor::GetPhysicalColor()
{
	return FColor::White;
}
FColor UGaldrarColor::GetTrueDamageColor()
{
	return FColor::White;
}

// GOLD
FColor UGaldrarColor::GetGoldColor()
{
	return FColor::FromHex("DAA520FF");
}

FColor UGaldrarColor::GetHealColor()
{
	return FColor::Green;
}
