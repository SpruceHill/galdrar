// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "BaseEffectComponent.h"
#include "HealEffectComponent.generated.h"

/**
 * 
 */
UCLASS()
class GALDRAR_API UHealEffectComponent : public UBaseEffectComponent
{
	GENERATED_BODY()

public:

	UHealEffectComponent();

	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	
};
