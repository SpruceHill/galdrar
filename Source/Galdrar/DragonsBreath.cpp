// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "DragonsBreath.h"
#include "BurnEffectComponent.h"

UDragonsBreath::UDragonsBreath()
{
	name = "Dragon's Breath";
	desc = "Shoot a ball of fire onto your enemies - dealing 20 fire damage to everyone in its path and sets them on fire.";
	activation = EActivation::TARGET_GROUND;
	spellTarget = ESpellTarget::CONE;
	resourceType = EResourceType::MANA;
	manaCost = 40.f;
	radius = 200.f;
	bProjectile = true;
	bDoesDamage = true;

	damage = 20.f;
	cooldown = 5.f;
	time = 0.f;
	effectTypes.Add(UBurnEffectComponent::StaticClass());
	damageType = EGaldrarDamageType::FIRE;
	range = 600.f;

	// 2 = Spell, ID = 0001
	ID = 20001;

	static ConstructorHelpers::FObjectFinder<UBlueprint> DBprojectileBlueprint(TEXT("Blueprint'/Game/SpellEffects/Projectiles/DragonsBreathProjectile'"));
	if (DBprojectileBlueprint.Object)
	{
		ProjectileReference = (UClass*)DBprojectileBlueprint.Object->GeneratedClass;
	}
}

void UDragonsBreath::ActivateAttack(FVector location, ABaseCharacter* target)
{
	time = cooldown;
	if (ABaseCharacter* character = dynamic_cast<ABaseCharacter*>(GetOwner()))
	{
		character->DecreaseMana(manaCost);
		FActorSpawnParameters SpawnParameters;
		ABaseProjectile* BPProjectile = GetWorld()->SpawnActor<ABaseProjectile>(ProjectileReference, character->GetActorLocation(), character->GetActorForwardVector().Rotation(), SpawnParameters);
		BPProjectile->Initialize(character, this);
	}
}
