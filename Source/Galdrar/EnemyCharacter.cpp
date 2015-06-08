// Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "EnemyCharacter.h"
#include "EnemyAIController.h"


AEnemyCharacter::AEnemyCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	maxHealth = 10;
	health = 1;
	name = "Dynamic";
	AIControllerClass = AEnemyAIController::StaticClass();
}

