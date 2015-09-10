// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "BaseTrait.h"
#include "BaseCharacter.h"
#include "Berserker.generated.h"

/**
 * 
 */
UCLASS()
class GALDRAR_API UBerserker : public UBaseTrait
{
	GENERATED_BODY()
	
public:
	UBerserker();

	virtual void ActivateTrait() override;
	
private:
	ABaseCharacter* owner;
};
