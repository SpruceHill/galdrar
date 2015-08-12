// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "BloodVialComponent.h"
#include "StandardBloodVial.generated.h"

/**
 * 
 */
UCLASS()
class GALDRAR_API UStandardBloodVial : public UBloodVialComponent
{
	GENERATED_BODY()
public:
	UStandardBloodVial();

	// Called when the game starts
	virtual void InitializeComponent() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Use() override;

private:
	int8 healAmount;
};
