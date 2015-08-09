// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "BaseEffectComponent.h"
#include "GasCloudEffectComponent.generated.h"

/**
 * 
 */
UCLASS()
class GALDRAR_API UGasCloudEffectComponent : public UBaseEffectComponent
{
	GENERATED_BODY()
	
public:
	UGasCloudEffectComponent();

	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
