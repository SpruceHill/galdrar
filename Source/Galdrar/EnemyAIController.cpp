// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "EnemyAIController.h"
#include "EnemyCharacter.h"

AEnemyAIController::AEnemyAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	blackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	behaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
}

void AEnemyAIController::Possess(class APawn* inPawn)
{

}

void AEnemyAIController::SetEnemy(class APawn inPawn)
{

}
void AEnemyAIController::SearchForEnemy()
{

}