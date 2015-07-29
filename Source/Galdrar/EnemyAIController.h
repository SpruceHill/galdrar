// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "AIController.h"
#include "EnemyCharacter.h"
#include "EnemyAIController.generated.h"


/**
 * 
 */
UCLASS()
class GALDRAR_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AEnemyAIController(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(transient)
	class UBlackboardComponent* blackboardComp;
	
	UPROPERTY(transient)
	class UBehaviorTreeComponent* behaviorTreeComp;

	virtual void Possess(class APawn* inPawn);

	void SetEnemy(class APawn* inPawn);

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void SearchForEnemy();

protected:
	uint8 enemyKeyID;
	uint8 enemyLocationID;

	float aggroDistance = 400.f;

	AEnemyCharacter* persistantPawn;
	bool bIsPossessing;
};
