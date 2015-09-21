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

UENUM(BlueprintType)
namespace EArmorSlot
{
	enum Type
	{
		AS_HEAD		UMETA(DisplayName = "Head"),
		AS_CHEST	UMETA(DisplayName = "Chest"),
		AS_HANDS	UMETA(DisplayName = "Hands"),
		AS_FEET		UMETA(DisplayName = "Feet"),
		AS_SHIELD	UMETA(DisplayName = "Shield"),
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

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Armor, meta = (AllowPrivateAccess = "true"))
	TEnumAsByte<EArmorSlot::Type> armorSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Armor, meta = (AllowPrivateAccess = "true"))
	bool isSlave;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Armor, meta = (AllowPrivateAccess = "true"))
	float weight;
};
