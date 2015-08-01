// Spruce Hill, All rights reserved.

#pragma once

#include "BaseCharacter.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GALDRAR_API AEnemyCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = BaseCharacter, meta = (AllowPrivateAccess = "true"))
	//class UCapsuleComponent* CursorHitbox;

	AEnemyCharacter(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, Category = Behavior)
	class UBehaviorTree* botBehavior;

	UFUNCTION(BlueprintCallable, Category = Enemy)
	int32 GetLevel();

	UFUNCTION(BlueprintCallable, Category = Enemy)
	void SetLevel(int32 newLevel);

protected:
	// Level used to generate name color 1-5
	UPROPERTY(EditAnywhere, Category = Enemy)
	int32 level;
};
