// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "Loot.h"
#include "Valuable.generated.h"

/**
 * 
 */
UCLASS(abstract)
class GALDRAR_API AValuable : public ALoot
{
	GENERATED_BODY()
public:

	int32 GetValue(){ return value; }
protected:
	UPROPERTY(BlueprintReadWrite, Category = Loot)
	int32 value;
};
