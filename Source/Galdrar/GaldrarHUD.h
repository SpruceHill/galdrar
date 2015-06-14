// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "GameFramework/HUD.h"
#include "BaseCharacter.h"
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

	void CreateDamageIndicator(FVector location, float damage, DamageType type, bool crit);

	void SetFocusedCharacter(ABaseCharacter* character) { focusedCharacter = character; }
	ABaseCharacter* GetFocusedCharacter() { return focusedCharacter; }

	UPROPERTY(BlueprintReadWrite, Category = hud)
	ABaseCharacter* focusedCharacter;
};
