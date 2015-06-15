// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "GaldrarHUD.h"
#include "HeroPlayerController.h"
#include "BaseCharacter.h"
#include "DamageIndicator.h"

void AGaldrarHUD::DrawHUD()
{
	Super::DrawHUD();
}

/*void AGaldrarHUD::CreateDamageIndicator(FVector location, float damage, DamageType type, bool crit)
{
	UWorld* World = GetWorld();
	if (World)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, location.ToString());
		ADamageIndicator* DI = World->SpawnActor<ADamageIndicator>(ADamageIndicator::StaticClass());
		DI->SetProperties(location, damage, type, crit);
		DI->SetActorLocation(location);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, DI->GetActorLocation().ToString());
	}
}*/