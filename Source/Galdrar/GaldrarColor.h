// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "DamageType.h"
#include "GaldrarColor.generated.h"

/**
 * 
 */
UCLASS()
class GALDRAR_API UGaldrarColor : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static FColor GetDamageTypeColor(DamageType type);

	UFUNCTION(BlueprintCallable, Category = Color)
	static FColor GetLevelColor(int32 level);
	
	//DAMAGE TYPES
	UFUNCTION(BlueprintCallable, Category = Color)
	static FColor GetFireColor();
	UFUNCTION(BlueprintCallable, Category = Color)
	static FColor GetFrostColor();
	UFUNCTION(BlueprintCallable, Category = Color)
	static FColor GetShockColor();
	UFUNCTION(BlueprintCallable, Category = Color)
	static FColor GetPoisonColor();
	UFUNCTION(BlueprintCallable, Category = Color)
	static FColor GetPhysicalColor();
	UFUNCTION(BlueprintCallable, Category = Color)
	static FColor GetTrueDamageColor();

	// GOLD
	UFUNCTION(BlueprintCallable, Category = Color)
	static FColor GetGoldColor();

	// HEAL
	UFUNCTION(BlueprintCallable, Category = Color)
	static FColor GetHealColor();

};
