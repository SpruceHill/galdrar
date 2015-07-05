// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "ProjectileFactory.h"
#include "BaseProjectile.h"

void UProjectileFactory::SpawnProjectile(ABaseCharacter* caster, FVector targetLocation, Attack* attack)
{
	//ABaseProjectile* MyObject = ConstructObject<ABaseProjectile>(ABaseProjectile::StaticClass());
	/*static ConstructorHelpers::FClassFinder<ABaseProjectile> ThisResource(TEXT("/Game/DragonsBreathProjectile"));
	if (ThisResource.Class != NULL)
	{
		UClass* DragonsBreathProjectile = ThisResource.Class;
		ABaseProjectile* NewProjectile = world->SpawnActor<ABaseProjectile*>(DragonsBreathProjectile, location, FRotator(0,0,0), NULL);
	}*/
}
