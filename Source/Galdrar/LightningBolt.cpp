// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "LightningBolt.h"

ULightningBolt::ULightningBolt()
{
	name = "Lighning Bolt";
	desc = "Shoot a bolt that electrecutes your foes.";
	activation = EActivation::TARGET_GROUND;
	spellTarget = ESpellTarget::CONE;
	manaCost = 10.f;
	radius = 50.f;
	bProjectile = true;
	bDoesDamage = true;

	damage = 25.f;
	cooldown = 5.f;
	time = 0.f;
	damageType = EGaldrarDamageType::SHOCK;
	range = 700.f;

	// 2 = Spell, ID = 0005
	ID = 20005;

	static ConstructorHelpers::FObjectFinder<UBlueprint> DBprojectileBlueprint(TEXT("Blueprint'/Game/SpellEffects/Projectiles/LightningBoltProjectile'"));
	if (DBprojectileBlueprint.Object)
	{
		blueprintReference = (UClass*)DBprojectileBlueprint.Object->GeneratedClass;
	}
}

void ULightningBolt::ActivateAttack(FVector location, ABaseCharacter* target)
{
	time = cooldown;
	if (ABaseCharacter* character = dynamic_cast<ABaseCharacter*>(GetOwner()))
	{
		character->DecreaseMana(manaCost);
		FActorSpawnParameters SpawnParameters;
		ABaseProjectile* BPProjectile = GetWorld()->SpawnActor<ABaseProjectile>(blueprintReference, character->GetActorLocation(), character->GetActorForwardVector().Rotation(), SpawnParameters);
		BPProjectile->Initialize(character, this);
	}
}