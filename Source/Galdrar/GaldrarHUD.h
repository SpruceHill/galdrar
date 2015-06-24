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

	void SetFocusedCharacter(ABaseCharacter* character) { focusedCharacter = character; }
	
	ABaseCharacter* GetFocusedCharacter() { return focusedCharacter; }

	void SetFocusedLoot(ALoot* loot) { focusedLoot = loot; }
	ALoot* GetFocusedLoot() { return focusedLoot; }

	UPROPERTY(BlueprintReadWrite, Category = hud)
	ABaseCharacter* focusedCharacter;

	UPROPERTY(BlueprintReadWrite, Category = hud)
	ALoot* focusedLoot;
};
