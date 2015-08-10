// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "BaseEffectComponent.h"
#include "ManaRegenerationEffectComponent.generated.h"

/**
 * 
 */
UCLASS()
class GALDRAR_API UManaRegenerationEffectComponent : public UBaseEffectComponent
{
	GENERATED_BODY()
	
public:
	UManaRegenerationEffectComponent();

	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Remove() override;
};
