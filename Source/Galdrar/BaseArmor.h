// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "BaseArmor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GALDRAR_API UBaseArmor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseArmor();

	UFUNCTION(BlueprintCallable, Category = Armor)
	virtual void InitializeArmor();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
	
};
