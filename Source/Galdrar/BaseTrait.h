// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "Components/ActorComponent.h"
#include "BaseTrait.generated.h"

UENUM(BlueprintType)
namespace ETraitActivation
{
	enum Type
	{
		ON_ATTACKED		UMETA(DisplayName = "On Attacked"),
		ON_ATTACKING	UMETA(DisplayName = "On Attacking"),
		ON_USEITEM		UMETA(DisplayName = "On Use Item"),
		ON_CREATION		UMETA(DisplayName = "On Creation"),
	};
}

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GALDRAR_API UBaseTrait : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBaseTrait();

	// Called when the game starts
	virtual void InitializeComponent() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	
	// Should be called as soon as the activation state is reached.
	UFUNCTION(BlueprintCallable, Category = Trait)
	virtual void ActivateTrait();

protected:
	UPROPERTY(BlueprintReadWrite, Category = Trait)
	FString name;
	UPROPERTY(BlueprintReadWrite, Category = Trait)
	FString desc;

	UPROPERTY(BlueprintReadWrite, Category = EffectComponent)
	TEnumAsByte<ETraitActivation::Type> traitActivation = ETraitActivation::Type::ON_CREATION;
};
