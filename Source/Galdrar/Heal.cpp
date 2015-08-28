// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "Heal.h"


UHeal::UHeal()
{
	name = "Heal";
	desc = "+40 health to target.";
	activation = EActivation::SELF;
	spellTarget = ESpellTarget::UNIT;
	resourceType = EResourceType::MANA;
	manaCost = 15.f;
	radius = 50.f;
	bProjectile = false;
	bDoesDamage = false;

	damage = 40.f;
	cooldown = 30.f;
	time = 0.f;
	damageType = EGaldrarDamageType::NONE;
	range = 1000.f;

	// 2 = Spell, ID = 0003
	ID = 20003;

	static ConstructorHelpers::FObjectFinder<UBlueprint> DBprojectileBlueprint(TEXT("Blueprint'/Game/SpellEffects/HealEffect'"));
	if (DBprojectileBlueprint.Object)
	{
		blueprintReference = (UClass*)DBprojectileBlueprint.Object->GeneratedClass;
	}
}

void UHeal::ActivateAttack(FVector location, ABaseCharacter* target)
{
	time = cooldown;
	if (ABaseCharacter* character = dynamic_cast<ABaseCharacter*>(GetOwner()))
	{
		character->DecreaseMana(manaCost);
		FActorSpawnParameters SpawnParameters;
		ASpellEffect* BPProjectile = GetWorld()->SpawnActor<ASpellEffect>(blueprintReference, target->GetActorLocation(), FRotator(0, 0, 0), SpawnParameters);
		if (BPProjectile) BPProjectile->Initialize(character, this);
		character->Heal(damage);
	}
}
