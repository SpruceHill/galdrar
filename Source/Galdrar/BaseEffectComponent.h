// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "GaldrarDamageType.h"
#include "BaseEffectComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GALDRAR_API UBaseEffectComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBaseEffectComponent();

	// Called when the game starts
	virtual void InitializeComponent() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	virtual void Remove();

	UFUNCTION(BlueprintCallable, Category = EffectComponent)
	FString GetName();

	UFUNCTION(BlueprintCallable, Category = EffectComponent)
	FString GetDesc();

	UFUNCTION(BlueprintCallable, Category = EffectComponent)
	bool IsDefensive();

	UFUNCTION(BlueprintCallable, Category = EffectComponent)
	float GetDamage();

	UFUNCTION(BlueprintCallable, Category = EffectComponent)
	float GetTime();

	UFUNCTION(BlueprintCallable, Category = EffectComponent)
	float GetDuration();

	UFUNCTION(BlueprintCallable, Category = EffectComponent)
	float GetElapsedTime();

	UFUNCTION(BlueprintCallable, Category = EffectComponent)
	EGaldrarDamageType GetDamageType();

	UFUNCTION(BlueprintCallable, Category = EffectComponent)
	int32 GetID();

	UFUNCTION(BlueprintCallable, Category = EffectComponent)
	void ResetTimer();

	bool bStackable;
	bool bShouldTick;
	bool bRemoveOnDamageTaken;

protected:
	bool bDefensive;

	float duration;
	float tickRate;

	float time;
	float elapsedTime;

	float damage;
	int32 ID;
	FString name;
	FString desc;
	FString toBePrinted;
	EGaldrarDamageType damageType;
};
