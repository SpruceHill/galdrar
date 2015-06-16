// Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "EnemyCharacter.h"
#include "EnemyAIController.h"
#include "BaseCharacter.h"


AEnemyCharacter::AEnemyCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	maxHealth = 100.f;
	health = 100.f;
	name = "Old Name";
	armour = 1;
	fireResistance = 1;
	frostResistance = 1;
	shockResistance = 1;
	AIControllerClass = AEnemyAIController::StaticClass();

	// Configure character movement
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 200.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
}
