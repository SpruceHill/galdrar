// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "HeroCharacter.h"
#include "BaseArmorActor.generated.h"


UENUM(BlueprintType)
namespace EArmorColor
{
	enum Type
	{
		AC_RED		UMETA(DisplayName = "Red"),
		AC_BLUE		UMETA(DisplayName = "Blue"),
		AC_GREEN	UMETA(DisplayName = "Green"),
		AC_YELLOW	UMETA(DisplayName = "Yellow"),
		AC_BLACK	UMETA(DisplayName = "Black"),
		AC_WHITE	UMETA(DisplayName = "White"),
		AC_NONE		UMETA(DisplayName = "No Dye"),
	};
}

UCLASS()
class GALDRAR_API ABaseArmorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseArmorActor();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = Armor)
	void InitializeArmor(AHeroCharacter* hero, EArmorColor::Type color);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
