// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "Loot.generated.h"

/*
* This class represents everything that can be picked up in the world.
*/
UCLASS(abstract)
class GALDRAR_API ALoot : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALoot();
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	FString GetName() { return name; }
	FString GetDesc() { return desc; }

protected:
	UPROPERTY(BlueprintReadWrite, Category = Loot)
	FString name;
	UPROPERTY(BlueprintReadWrite, Category = Loot)
	FString desc;	
};
