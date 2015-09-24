// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "BaseEffectComponent.h"
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
	virtual void ActivateAttack(FVector location, ABaseCharacter* target);
	
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

	UFUNCTION(BlueprintCallable, Category = Weapon)
	float GetNextAttackDelay();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	bool bDoesDamage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	TEnumAsByte<EGaldrarDamageType> damageType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float damage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float critMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float range;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float attackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	TArray<TSubclassOf<UBaseEffectComponent>> effectTypes;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	FString name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	FString desc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float cooldown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	bool bProjectile;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	bool bProjectilePenetration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float projectileWidth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float projectileSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float ID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Armor, meta = (AllowPrivateAccess = "true"))
	TArray<float> animationAttackDelay;

private:
	int8 animationIndex = 0;
};
