// Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "EnemyCharacter.h"
#include "EnemyAIController.h"


AEnemyCharacter::AEnemyCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	maxHealth = 100.f;
	health = 100.f;
	name = "Old Name";
	armour = 1;
	AIControllerClass = AEnemyAIController::StaticClass();
	drawHealthbar = false;
}
