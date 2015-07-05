// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "BaseCharacter.h"
#include "Attack.h"
#include "BaseProjectile.generated.h"

UCLASS()
class GALDRAR_API ABaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseProjectile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = Projectile)
	void Hit(AActor* actor);

	//void SetDirection(FVector targetLocation){ this->targetLocation = targetLocation; }
	void Initialize(ABaseCharacter* caster, Attack* attack)
	{ 
		this->caster = caster;
		this->attack = attack; 
		bPenetrating = attack->IsProjectilePenetrating();
		speed = attack->GetProjectileSpeed();
		width = attack->GetProjectileWidth();
		range = attack->GetRange();
	}

	TSubclassOf<class ABaseProjectile> BluePrintReference;

protected:
	UPROPERTY(BlueprintReadOnly, Category = Projectile)
	bool bPenetrating;
	UPROPERTY(BlueprintReadOnly, Category = Projectile)
	float speed;
	UPROPERTY(BlueprintReadOnly, Category = Projectile)
	float width;
	UPROPERTY(BlueprintReadOnly, Category = Projectile)
	float range;
	//FVector targetLocation;
	UPROPERTY(BlueprintReadOnly, Category = Projectile)
	ABaseCharacter* caster;
	Attack* attack;
	UPROPERTY(BlueprintReadOnly, Category = Projectile)
	FVector origin;
};
