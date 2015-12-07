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

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(transient)
	class UBlackboardComponent* blackboardComp;
	
	UPROPERTY(transient)
	class UBehaviorTreeComponent* behaviorTreeComp;

	virtual void Possess(class APawn* inPawn);

	void SetEnemy(class APawn* inPawn);

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void SearchForEnemy();

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void WalkRandomly();

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void Attack();

protected:
	uint8 enemyKeyID;
	uint8 enemyLocationID;

	float aggroDistance;
	float loseTrackDistance;

	AEnemyCharacter* persistantPawn;
	bool bIsPossessing;

	FVector pawnOrigin;
	float maxWalkRadius;

private:
	void AttackDelay();
};
