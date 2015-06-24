// Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "EnemyCharacter.h"
#include "EnemyAIController.h"
#include "BaseCharacter.h"
#include "BurnEffect.h"

AEnemyCharacter::AEnemyCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	name = "Old Name";

	stats = new CharacterStats();
	stats->defaultRotationRate = 200.f;
	stats->rotationRate = 200.f;
	stats->defaultMovementSpeed = 200.f;
	stats->movementSpeed = 200.f;
	
	AddEffect(new BurnEffect(stats));

	AIControllerClass = AEnemyAIController::StaticClass();

	// Configure character movement
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 200.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 200.f;
}
