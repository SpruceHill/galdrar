// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "BaseProjectile.h"
#include "CombatHandler.h"


// Sets default values
ABaseProjectile::ABaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Dragon's Breath
	static ConstructorHelpers::FObjectFinder<UBlueprint> DBprojectileBlueprint(TEXT("Blueprint'/Game/SpellEffects/Projectiles/DragonsBreathProjectile'"));
	if (DBprojectileBlueprint.Object)
	{
		DragonsBreathBluePrintReference = (UClass*)DBprojectileBlueprint.Object->GeneratedClass;
	}

	// Javelin
	static ConstructorHelpers::FObjectFinder<UBlueprint> JprojectileBlueprint(TEXT("Blueprint'/Game/SpellEffects/Projectiles/JavelinProjectile'"));
	if (JprojectileBlueprint.Object)
	{
		JavelinBluePrintReference = (UClass*)JprojectileBlueprint.Object->GeneratedClass;
	}

	// Lightning Bolt
	static ConstructorHelpers::FObjectFinder<UBlueprint> LBprojectileBlueprint(TEXT("Blueprint'/Game/SpellEffects/Projectiles/LightningBoltProjectile'"));
	if (LBprojectileBlueprint.Object)
	{
		LightningBoltBluePrintReference = (UClass*)LBprojectileBlueprint.Object->GeneratedClass;
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
