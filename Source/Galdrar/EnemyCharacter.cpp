// Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "EnemyCharacter.h"
#include "EnemyAIController.h"
#include "BaseCharacter.h"


AEnemyCharacter::AEnemyCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	name = "Old Name";
	stats = new CharacterStats();
	stats->maxHealth = 100.f;
	stats->health = 100.f;
	stats->armour = 1;
	stats->fireResistance = 1;
	stats->frostResistance = 1;
	stats->shockResistance = 1;
	AIControllerClass = AEnemyAIController::StaticClass();

	// Configure character movement
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 200.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
}
