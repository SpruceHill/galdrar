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
	level = 1;
	stats = new CharacterStats();
	this->GetMesh()->bReceivesDecals = false;
	
	AIControllerClass = AEnemyAIController::StaticClass();

	// Configure character movement
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction

	CursorHitbox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CursorHitbox"));
	CursorHitbox->SetCollisionProfileName(TEXT("UI"));
	CursorHitbox->AttachParent = RootComponent;
}

int32 AEnemyCharacter::GetLevel()
{
	return level;
}

void AEnemyCharacter::SetLevel(int32 newLevel)
{
	level = newLevel;
}
