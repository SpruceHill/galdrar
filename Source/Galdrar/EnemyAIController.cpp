// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "EnemyAIController.h"
#include "BaseCharacter.h"
#include "HeroCharacter.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/BlackboardComponent.h"

AEnemyAIController::AEnemyAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	blackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	behaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
}

void AEnemyAIController::Possess(class APawn* inPawn)
{
	Super::Possess(inPawn);
	AEnemyCharacter* bot = Cast<AEnemyCharacter>(inPawn);
	if (bot && bot->botBehavior)
	{
		bIsPossessing = true;
		if (!persistantPawn) persistantPawn = bot;

		blackboardComp->InitializeBlackboard(*(bot->botBehavior->BlackboardAsset));
		enemyKeyID = blackboardComp->GetKeyID("Enemy");
		enemyLocationID = blackboardComp->GetKeyID("Destination");

		behaviorTreeComp->StartTree(*(bot->botBehavior));
	}
}

void AEnemyAIController::SetEnemy(class APawn* inPawn)
{
	blackboardComp->SetValue<UBlackboardKeyType_Object>(enemyKeyID, inPawn);
	blackboardComp->SetValue<UBlackboardKeyType_Vector>(enemyLocationID, inPawn->GetActorLocation());

	// Rotate attacker towards the target
	FVector newLookAt = inPawn->GetActorLocation().operator-=(GetPawn()->GetActorLocation());
	newLookAt.Z = 1; // Make sure character is always upright (attacking on stairs etc.)
	GetPawn()->SetActorRotation(newLookAt.Rotation());
}

void AEnemyAIController::SearchForEnemy()
{
	ABaseCharacter* bot = Cast<ABaseCharacter>(GetPawn());
	if (bot == NULL) { GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, "BOT NULL"); return; }

	const FVector location = bot->GetActorLocation();
	float bestDistanceSquared = MAX_FLT;
	
	// Find the hero closest to this enemy
	AHeroCharacter* bestPawn = NULL;
	for (FConstPawnIterator it = GetWorld()->GetPawnIterator(); it; ++it)
	{
		AHeroCharacter* testPawn = Cast<AHeroCharacter>(*it);
		if (testPawn)
		{
			const float distanceSquared = FVector::Dist(testPawn->GetActorLocation(), location);
			if (distanceSquared < bestDistanceSquared && distanceSquared < aggroDistance)
			{
				bestDistanceSquared = distanceSquared;
				bestPawn = testPawn;
			}
		}
	}
	if (bestPawn)
	{
		SetEnemy(bestPawn);
		bot->GetStats()->movementSpeed = bot->GetStats()->defaultMovementSpeed; // TODO FIX
	}
}

void AEnemyAIController::WalkRandomly()
{
	// Don't assign a new place to walk if the pawn is already in motion
	if (GetPawn()->GetMovementComponent()->Velocity.Size() > 20) return;
	
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(GetPawn());
	EnemyCharacter->GetStats()->movementSpeed = 150; // TODO let each BaseCharacter decide its walk speed. (Adjust maxmovementspeed)

	int32 DeltaX = FMath::RandRange(-500, 500);
	int32 DeltaY = FMath::RandRange(-500, 500);
	
	const FVector DestLocation = FVector(
		EnemyCharacter->GetActorLocation().X + DeltaX, 
		EnemyCharacter->GetActorLocation().Y + DeltaY, 
		EnemyCharacter->GetActorLocation().Z
		);
	
	if (EnemyCharacter)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, EnemyCharacter->GetActorLocation());

		// Walk if far enough or ordered stand still (HACK)
		if (NavSys && ((Distance > 120.0f) || DestLocation == EnemyCharacter->GetActorLocation()))
		{
			NavSys->SimpleMoveToLocation(this, DestLocation);
		}
	}
}
