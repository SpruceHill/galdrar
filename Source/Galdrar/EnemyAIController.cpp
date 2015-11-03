// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "EnemyAIController.h"
#include "BaseCharacter.h"
#include "HeroCharacter.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIDeterrentFilter.h"
#include "AIBlockFilter.h"

AEnemyAIController::AEnemyAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	blackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	behaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));

	aggroDistance = 400.f;
	maxWalkRadius = 600.f;
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

		pawnOrigin = bot->GetActorLocation();
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
	AEnemyCharacter* bot = Cast<AEnemyCharacter>(GetPawn());
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
				if (LineOfSightTo(testPawn))
				{
					bestDistanceSquared = distanceSquared;
					bestPawn = testPawn;
				}
			}
		}
	}
	if (bestPawn)
	{
		SetEnemy(bestPawn);
		bot->ShouldWalk(false);
	}
}

void AEnemyAIController::WalkRandomly()
{
	// Don't assign a new place to walk if the pawn is already in motion
	if (GetPawn()->GetMovementComponent()->Velocity.Size() > 20) return;
	
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(GetPawn());

	if (EnemyCharacter)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();

		FVector randomNavPoint = NavSys->GetRandomPointInNavigableRadius
			(
			GetWorld(),
			pawnOrigin,
			maxWalkRadius,
			NULL,
			UAIBlockFilter::StaticClass()
			);

		// Don't take too small steps, allow animation to play out
		if (NavSys && FVector::Dist(EnemyCharacter->GetActorLocation(), randomNavPoint) > 120.0f)
		{
			EnemyCharacter->ShouldWalk(true);
			MoveToLocation(randomNavPoint, 50.f, true, true, true, false, UAIBlockFilter::StaticClass(), true);
		}
	}
}
