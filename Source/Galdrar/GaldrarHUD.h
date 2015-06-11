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

	void SetFocusedCharacter(ABaseCharacter* character) { focusedCharacter = character; }

	//UFUNCTION(BlueprintCallable, Category = hud)
	ABaseCharacter* GetFocusedCharacter() { return focusedCharacter; }
	UPROPERTY(BlueprintReadOnly, Category = hud)
	ABaseCharacter* focusedCharacter;
	
private:
	void DrawHealthbar(ABaseCharacter* character);
};
