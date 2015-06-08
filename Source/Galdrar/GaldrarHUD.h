// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "GameFramework/HUD.h"
#include "GaldrarHUD.generated.h"

/**
 * 
 */
UCLASS()
class GALDRAR_API AGaldrarHUD : public AHUD
{
	GENERATED_BODY()
	
	virtual void DrawHUD() override;

private:
	/** Draw functions*/
	void DrawHealthbar();
	void DrawAbilitybar();
	
};
