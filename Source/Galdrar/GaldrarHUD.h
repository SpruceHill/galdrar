// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "GameFramework/HUD.h"
#include "BaseCharacter.h"
#include "Loot.h"
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

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = HUD)
	void Toast(const FString& text);

	UFUNCTION(BlueprintCallable, Category = "Spells")
	void RemoveAOETemplate();
	
	UFUNCTION(BlueprintCallable, Category = "Spells")
	void RemoveRangeIndicator();

	void SetFocusedCharacter(ABaseCharacter* character)
	{
		if (focusedCharacter)
		{
			// Stop highlighting old character
			focusedCharacter->GetMesh()->SetRenderCustomDepth(false);
		}
		focusedCharacter = character;
		// Highlight if valid
		if (character) character->GetMesh()->SetRenderCustomDepth(true);
	}
	
	ABaseCharacter* GetFocusedCharacter() { return focusedCharacter; }

	void SetFocusedLoot(ABaseInteractable* loot)
	{
		if (focusedLoot)
		{
			// Stop highlighting old character
			focusedLoot->GetMesh()->SetRenderCustomDepth(false);
		}
		focusedLoot = loot;
		// Highlight if valid
		if (loot) loot->GetMesh()->SetRenderCustomDepth(true);
	}

	ABaseInteractable* GetFocusedLoot() { return focusedLoot; }

	UPROPERTY(BlueprintReadWrite, Category = hud)
	ABaseCharacter* focusedCharacter;

	UPROPERTY(BlueprintReadWrite, Category = hud)
	ABaseInteractable* focusedLoot;

	UPROPERTY(BlueprintReadWrite, Category = hud)
	UDecalComponent* rangeIndicator;

	UPROPERTY(BlueprintReadWrite, Category = hud)
	UDecalComponent* AOEDecal;
};
