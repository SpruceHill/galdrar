// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "BaseEffectComponent.h"
#include "BurnEffectComponent.generated.h"

/**
 * 
 */
UCLASS()
class GALDRAR_API UBurnEffectComponent : public UBaseEffectComponent
{
	GENERATED_BODY()
	
public:
	UBurnEffectComponent();

	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Remove() override;
};
