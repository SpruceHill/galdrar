// Spruce Hill, All rights reserved.

#pragma once

#include "BaseCharacter.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GALDRAR_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = Behavior)
	class UBehaviorTree* botBehavior;
	
public:
	AEnemyCharacter(const FObjectInitializer& ObjectInitializer);
};
