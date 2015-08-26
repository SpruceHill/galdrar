// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "AttackComponent.h"


// Sets default values for this component's properties
UAttackComponent::UAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttackComponent::InitializeComponent()
{
	Super::InitializeComponent();

	// ...
	
}


// Called every frame
void UAttackComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

float UAttackComponent::GetDamage(){ return damage; }

EGaldrarDamageType UAttackComponent::GetDamageType(){ return damageType; }

float UAttackComponent::GetCritMultiplier(){ return critMultiplier; }

TArray<TSubclassOf<UBaseEffectComponent>> UAttackComponent::GetEffectTypes(){ return effectTypes; }

float UAttackComponent::GetRange(){ return range; }

float UAttackComponent::GetAttackSpeed(){ return attackSpeed; }

FString UAttackComponent::GetName(){ return name; }

FString UAttackComponent::GetDesc(){ return desc; }

bool UAttackComponent::IsProjectile(){ return bProjectile; }

bool UAttackComponent::IsProjectilePenetrating(){ return bProjectilePenetration; }

float UAttackComponent::GetProjectileWidth(){ return projectileWidth; }

float UAttackComponent::GetProjectileSpeed(){ return projectileSpeed; }

void UAttackComponent::ActivateAttack(FVector destination, ABaseCharacter* target){ return; }

bool UAttackComponent::IsOnCoolDown(){ return time > 0; }

float UAttackComponent::GetTime(){ return time; }

float UAttackComponent::GetCooldown(){ return cooldown; }

bool UAttackComponent::DoesDamage(){ return bDoesDamage; }

float UAttackComponent::GetID(){ return ID; }
