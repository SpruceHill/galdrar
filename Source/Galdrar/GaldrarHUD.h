// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "GameFramework/HUD.h"
#include "BaseCharacter.h"
#include "Loot.h"
#include "AOETemplate.h"
#include "GaldrarHUD.generated.h"

/**
 * 
 */
UCLASS()
class GALDRAR_API AGaldrarHUD : public AHUD
{
	GENERATED_BODY()
public:

	virtual void DrawHUD() override;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Damage")
	void CreateDamageIndicator(ABaseCharacter* character, const FString& text, FColor indicatorColor, bool crit);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Spells")
	void CreateAOECircle(ABaseCharacter* character, float radius, FColor damageTypeColor);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Spells")
	void CreateAOECone(ABaseCharacter* character, float range, float radius, FColor damageTypeColor);
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Spells")
	void CreateRangeIndicator(ABaseCharacter* character, float spellRange, FColor damageTypeColor);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = HUD)
	void CreateMovementLocationIndicator(FVector location);

	UFUNCTION(BlueprintCallable, Category = "Spells")
	void RemoveAOETemplate();
	
	UFUNCTION(BlueprintCallable, Category = "Spells")
	void RemoveRangeIndicator();

	void SetFocusedCharacter(ABaseCharacter* character) { focusedCharacter = character; }
	
	ABaseCharacter* GetFocusedCharacter() { return focusedCharacter; }

	void SetFocusedLoot(ALoot* loot) { focusedLoot = loot; }
	ALoot* GetFocusedLoot() { return focusedLoot; }

	UPROPERTY(BlueprintReadWrite, Category = hud)
	ABaseCharacter* focusedCharacter;

	UPROPERTY(BlueprintReadWrite, Category = hud)
	ALoot* focusedLoot;

	UPROPERTY(BlueprintReadWrite, Category = hud)
	UDecalComponent* rangeIndicator;

	UPROPERTY(BlueprintReadWrite, Category = hud)
	UDecalComponent* AOEDecal;
};
