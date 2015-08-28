// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "AttackComponent.h"
#include "BaseSpell.generated.h"

UENUM(BlueprintType)
namespace ESpellTarget
{
	enum Type
	{
		UNIT	UMETA(DisplayName = "Unit"),
		CIRCLE	UMETA(DisplayName = "Circle"),
		CONE	UMETA(DisplayName = "Cone"),
		AURA	UMETA(DisplayName = "Aura"),
	};
}
UENUM(BlueprintType)
namespace EActivation
{
	enum Type
	{
		TARGET_UNIT		UMETA(DisplayName = "Target Unit"),
		TARGET_GROUND	UMETA(DisplayName = "Target Ground"),
		PASSIVE			UMETA(DisplayName = "Passive"),
		ATTACK_MODIFIER	UMETA(DisplayName = "Attack Modifier"),
		SELF			UMETA(DisplayName = "Self"),
	};
}
UENUM(BlueprintType)
namespace EResourceType
{
	enum Type
	{
		MANA	UMETA(DisplayName = "Mana"),
		RAGE	UMETA(DisplayName = "Rage"),
	};
}
/**
 * 
 */
UCLASS()
class GALDRAR_API UBaseSpell : public UAttackComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Spell)
	TEnumAsByte<ESpellTarget::Type> GetSpellTarget();

	UFUNCTION(BlueprintCallable, Category = Spell)
	TEnumAsByte<EActivation::Type> GetActivation();

	UFUNCTION(BlueprintCallable, Category = Spell)
	TEnumAsByte<EResourceType::Type> GetResourceType();

	UFUNCTION(BlueprintCallable, Category = Spell)
	float GetManaCost();

	UFUNCTION(BlueprintCallable, Category = Spell)
	float GetRadius();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spell)
	TEnumAsByte<ESpellTarget::Type> spellTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spell)
	TEnumAsByte<EActivation::Type> activation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spell)
	TEnumAsByte<EResourceType::Type> resourceType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spell)
	float manaCost;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spell)
	float radius;
	
};
