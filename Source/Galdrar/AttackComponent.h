// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "BaseEffectComponent.h"
#include "BaseCharacter.h"
#include "AttackComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GALDRAR_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttackComponent();

	// Called when the game starts
	virtual void InitializeComponent() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UFUNCTION(BlueprintCallable, Category = Attack)
	float GetDamage();

	UFUNCTION(BlueprintCallable, Category = Attack)
	EGaldrarDamageType GetDamageType();
	
	UFUNCTION(BlueprintCallable, Category = Attack)
	float GetCritMultiplier();
	
	UFUNCTION(BlueprintCallable, Category = Attack)
	TArray<TSubclassOf<UBaseEffectComponent>> GetEffectTypes();
	
	UFUNCTION(BlueprintCallable, Category = Attack)
	float GetRange();
	
	UFUNCTION(BlueprintCallable, Category = Attack)
	float GetAttackSpeed();
	
	UFUNCTION(BlueprintCallable, Category = Attack)
	virtual FString GetName();
	
	UFUNCTION(BlueprintCallable, Category = Attack)
	FString GetDesc();

	UFUNCTION(BlueprintCallable, Category = Attack)
	bool IsProjectile();

	UFUNCTION(BlueprintCallable, Category = Attack)
	bool IsProjectilePenetrating();
	
	UFUNCTION(BlueprintCallable, Category = Attack)
	float GetProjectileWidth();
	
	UFUNCTION(BlueprintCallable, Category = Attack)
	float GetProjectileSpeed();

	UFUNCTION(BlueprintCallable, Category = Attack)
	virtual void ActivateAttack(FVector destination, ABaseCharacter* target);
	
	UFUNCTION(BlueprintCallable, Category = Attack)
	bool IsOnCoolDown();
	
	UFUNCTION(BlueprintCallable, Category = Attack)
	float GetTime();
	
	UFUNCTION(BlueprintCallable, Category = Attack)
	float GetCooldown();

	UFUNCTION(BlueprintCallable, Category = Attack)
	bool DoesDamage();

	UFUNCTION(BlueprintCallable, Category = Attack)
	float GetID();

protected:
	bool bDoesDamage;
	EGaldrarDamageType damageType;
	
	float damage;
	float critMultiplier;
	float range;
	float attackSpeed;

	TArray<TSubclassOf<UBaseEffectComponent>> effectTypes;
	
	FString name;
	FString desc;

	float cooldown;
	float time;

	bool bProjectile;
	bool bProjectilePenetration;
	float projectileWidth;
	float projectileSpeed;

	float ID;
};
