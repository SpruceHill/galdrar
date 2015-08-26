// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "BaseSpell.h"
#include "BaseProjectile.h"
#include "DragonsBreath.generated.h"

/**
 * 
 */
UCLASS()
class GALDRAR_API UDragonsBreath : public UBaseSpell
{
	GENERATED_BODY()
public:
	UDragonsBreath();
	
	void ActivateAttack(FVector location, ABaseCharacter* target) override;

private:
	TSubclassOf<class ABaseProjectile> ProjectileReference;
};
