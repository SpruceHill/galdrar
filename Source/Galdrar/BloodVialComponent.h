// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "BloodVialComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GALDRAR_API UBloodVialComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBloodVialComponent();

	// Called when the game starts
	virtual void InitializeComponent() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UFUNCTION(BlueprintCallable, Category = BloodVial)
	virtual void Use();

	UFUNCTION(BlueprintCallable, Category = BloodVial)
	FString GetName();

	UFUNCTION(BlueprintCallable, Category = BloodVial)
	FString GetDesc();

	UFUNCTION(BlueprintCallable, Category = BloodVial)
	int32 GetMaxCharges();

	UFUNCTION(BlueprintCallable, Category = BloodVial)
	int32 GetCharges();

	UFUNCTION(BlueprintCallable, Category = BloodVial)
	int32 GetID();

	UFUNCTION(BlueprintCallable, Category = BloodVial)
	void AddCharges(int32 nbrOfCharges);

protected:
	FString name;

	FString desc;

	int32 ID;

	// Number of charges that can be spent
	int32 maxCharges;
	// Current amount
	int32 charges;
	
};
