// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "SpellEffect.h"
#include "CombatHandler.h"


// Sets default values
ASpellEffect::ASpellEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UBlueprint> DBprojectileBlueprint(TEXT("Blueprint'/Game/SpellEffects/GasCloudSpellEffect'"));
	if (DBprojectileBlueprint.Object)
	{
		GasCloudBluePrintReference = (UClass*)DBprojectileBlueprint.Object->GeneratedClass;
	}
}

// Called when the game starts or when spawned
void ASpellEffect::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpellEffect::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ASpellEffect::Initialize(ABaseCharacter* caster, UAttackComponent* attack)
{
	this->caster = caster;
	this->attack = attack;
	this->time = attack->GetTime();
	TArray<AActor*> overlappingActors;
	GetOverlappingActors(overlappingActors, ABaseCharacter::StaticClass());
	for (AActor* actor : overlappingActors)
	{
		Trigger(actor);
	}
}

void ASpellEffect::Trigger(AActor* actor)
{
	if (ABaseCharacter* bc = dynamic_cast<ABaseCharacter*>(actor))
	{
		//if (caster && bc && attack) CombatHandler::AttackEnemy(caster, bc, attack);
	}
}
