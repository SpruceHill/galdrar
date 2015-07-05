// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "BaseProjectile.h"
#include "CombatHandler.h"


// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	static ConstructorHelpers::FObjectFinder<UBlueprint> MyCharacterBlueprint(TEXT("Blueprint'/Game/DragonsBreathProjectile'")); //You can obtain this reference from editor

	if (MyCharacterBlueprint.Object)
	{
		BluePrintReference = (UClass*)MyCharacterBlueprint.Object->GeneratedClass;
	}
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	origin = GetActorLocation();
}

// Called every frame
void ABaseProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ABaseProjectile::Hit(AActor* actor)
{
	if (ABaseCharacter* bc = dynamic_cast<ABaseCharacter*>(actor))
	{
		if (caster && bc && attack) CombatHandler::AttackEnemy(caster, bc, attack);
	}
}

