// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "BaseEffectComponent.h"
#include "BaseCharacter.h"


// Sets default values for this component's properties
UBaseEffectComponent::UBaseEffectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;

	bDefensive = false;
}


// Called when the game starts
void UBaseEffectComponent::InitializeComponent()
{
	Super::InitializeComponent();
	// ...
}


// Called every frame
void UBaseEffectComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

FString UBaseEffectComponent::GetName(){ return name; }

FString UBaseEffectComponent::GetDesc(){ return desc; }

bool UBaseEffectComponent::IsDefensive()
{
	return bDefensive;
}

void UBaseEffectComponent::Remove()
{
	if (ERS != EEffectRenderState::Type::NO_STATE)
	{
		if (ABaseCharacter* character = dynamic_cast<ABaseCharacter*>(GetOwner()))
		{
			character->RemoveEffectRenderState(EEffectRenderState::Type::ON_FIRE);
		}
	}

	MarkPendingKill();
	GetOwner()->RemoveOwnedComponent(this);
}

float UBaseEffectComponent::GetDamage() { return damage; }

float UBaseEffectComponent::GetTime() { return time; }

float UBaseEffectComponent::GetDuration() { return duration; }

float UBaseEffectComponent::GetElapsedTime() { return elapsedTime; }

EGaldrarDamageType UBaseEffectComponent::GetDamageType() { return damageType; }

int32 UBaseEffectComponent::GetID(){ return ID; }

void UBaseEffectComponent::ResetTimer(){ elapsedTime = 0.f; }

void UBaseEffectComponent::SetRenderState(EEffectRenderState::Type RS)
{
	ERS = RS;
	if (RS != EEffectRenderState::Type::NO_STATE)
	{
		if (ABaseCharacter* character = dynamic_cast<ABaseCharacter*>(GetOwner()))
		{
			character->AddEffectRenderState(RS);
		}
	}
}
