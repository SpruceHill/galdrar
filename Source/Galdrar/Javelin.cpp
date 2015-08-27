// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "Javelin.h"

UJavelin::UJavelin()
{
	name = "Javelin";
	desc = "Hurtle a spear in any direction. Stunning on impact.";
	activation = EActivation::TARGET_GROUND;
	spellTarget = ESpellTarget::CONE;
	manaCost = 30.f;
	radius = 50.f;
	bProjectile = true;
	bDoesDamage = true;

	damage = 30.f;
	cooldown = 5.f;
	time = 0.f;
	damageType = EGaldrarDamageType::PHYSICAL;
	range = 1600.f;

	// 2 = Spell, ID = 0004
	ID = 20004;

	static ConstructorHelpers::FObjectFinder<UBlueprint> DBprojectileBlueprint(TEXT("Blueprint'/Game/SpellEffects/Projectiles/JavelinProjectile'"));
	if (DBprojectileBlueprint.Object)
	{
		blueprintReference = (UClass*)DBprojectileBlueprint.Object->GeneratedClass;
	}
}

void UJavelin::ActivateAttack(FVector location, ABaseCharacter* target)
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


