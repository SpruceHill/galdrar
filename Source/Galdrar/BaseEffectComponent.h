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

	bool IsDefensive();

	float GetDamage() { return damage; }
	float GetTime() { return time; }
	float GetDuration() { return duration; }
	float GetElapsedTime() { return elapsedTime; }

	EGaldrarDamageType GetDamageType() { return damageType; }

	int32 GetID(){ return ID; }

	void ResetTimer()
	{
		elapsedTime = 0.f;
	}

	void End()
	{
		elapsedTime = duration;
	}

	FString GetPrint(){ bPrintDI = false; return toBePrinted; }

	bool bStackable;
	bool doDamage;
	bool bShouldTick;
	bool bPrintDI;
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
