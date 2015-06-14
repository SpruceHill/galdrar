// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "EnemyAIController.h"
#include "EnemyCharacter.h"
#include "HeroCharacter.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
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
}
void AEnemyAIController::SearchForEnemy()
{
	APawn* bot = GetPawn();
	if (bot == NULL) { return; }
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
	}
}