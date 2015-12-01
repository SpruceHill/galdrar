// Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "EnemyCharacter.h"
#include "EnemyAIController.h"
#include "BaseCharacter.h"
#include "BotWeapon.h"

AEnemyCharacter::AEnemyCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	name = "Old Name";
	level = 1;
	stats = CreateDefaultSubobject<UCharacterStatsComponent>(TEXT("Stats"));
	this->GetMesh()->bReceivesDecals = false;
	weapon = CreateDefaultSubobject<UBotWeapon>(TEXT("Weapon"));
	
	AIControllerClass = AEnemyAIController::StaticClass();

	// Configure character movement
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction

	CursorHitbox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CursorHitbox"));
	CursorHitbox->SetCollisionProfileName(TEXT("UI"));
	CursorHitbox->AttachParent = RootComponent;

	GetCharacterMovement()->MaxWalkSpeedCrouched = 100.f;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->CrouchedHalfHeight = GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
}

int32 AEnemyCharacter::GetLevel()
{
	return level;
}

void AEnemyCharacter::SetLevel(int32 newLevel)
{
	level = newLevel;
}

void AEnemyCharacter::ShouldWalk(bool shouldWalk)
{
	GetCharacterMovement()->bWantsToCrouch = shouldWalk;
}
