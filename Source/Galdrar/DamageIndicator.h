// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "DamageType.h"
#include "GameFramework/Actor.h"
#include "DamageIndicator.generated.h"

UCLASS()
class GALDRAR_API ADamageIndicator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADamageIndicator(const FObjectInitializer& ObjectInitializer);
	void SetProperties(FVector location, float damage, DamageType type, bool crit);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

protected:
	//UPROPERTY(BlueprintReadOnly, Category = hud)
	float damage;
	UPROPERTY(BlueprintReadOnly, Category = hud)
	FColor attackTypeColor;
	UPROPERTY(BlueprintReadOnly, Category = hud)
	bool crit;
	UPROPERTY(BlueprintReadOnly, Category = hud)
	FVector characterLocation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = SpawningBP)
	TSubclassOf<ADamageIndicator> BlueprintVar;
};
