// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "BaseWeapon.h"

float UBaseWeapon::GetWeight()
{
	return weight;
}
int32 UBaseWeapon::GetKills()
{
	return kills;
}
bool UBaseWeapon::IsTwoHanded()
{
	return twoHanded;
}
