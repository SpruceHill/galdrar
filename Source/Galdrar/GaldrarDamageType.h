// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "Engine/UserDefinedEnum.h"
#include "GaldrarDamageType.generated.h"

/**
 * 
 */
UENUM(BlueprintType)    
enum EGaldrarDamageType
{
	FIRE		UMETA(DisplayName = "Fire"),
	FROST		UMETA(DisplayName = "Frost"),
	SHOCK		UMETA(DisplayName = "Shock"),
	POISON		UMETA(DisplayName = "Poison"),
	PHYSICAL	UMETA(DisplayName = "Physical"),
};


