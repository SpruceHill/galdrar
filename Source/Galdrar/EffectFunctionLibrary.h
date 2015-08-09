// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "BaseCharacter.h"
#include "EffectFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class GALDRAR_API UEffectFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static void GenerateEffect(ABaseCharacter* character, TSubclassOf<UBaseEffectComponent> effectType);
	static bool IsDefensive(TSubclassOf<UBaseEffectComponent> effectType);
};
