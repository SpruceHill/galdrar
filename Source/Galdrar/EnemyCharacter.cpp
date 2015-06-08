// Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "EnemyCharacter.h"
#include "EnemyAIController.h"


AEnemyCharacter::AEnemyCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	maxHealth = 100;
	health = maxHealth;
	name = "Malarn";
	AIControllerClass = AEnemyAIController::StaticClass();
}

