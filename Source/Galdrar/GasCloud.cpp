// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "GasCloud.h"
#include "GasCloudEffectComponent.h"

UGasCloud::UGasCloud()
{
	name = "Gas Cloud";
	desc = "Summon a cloud of poisonous gas.";
	activation = EActivation::TARGET_GROUND;
	spellTarget = ESpellTarget::CIRCLE;
	resourceType = EResourceType::MANA;
	manaCost = 20.f;
	radius = 300.f;
	bProjectile = false;
	bDoesDamage = false;

	damage = 0.f;
	cooldown = 5.f;
	time = 0.f;
	effectTypes.Add(UGasCloudEffectComponent::StaticClass());
	damageType = EGaldrarDamageType::POISON;
	range = 600.f;

	// 2 = Spell, ID = 0002
	ID = 20002;

	static ConstructorHelpers::FObjectFinder<UBlueprint> DBprojectileBlueprint(TEXT("Blueprint'/Game/SpellEffects/GasCloudSpellEffect'"));
	if (DBprojectileBlueprint.Object)
	{
		blueprintReference = (UClass*)DBprojectileBlueprint.Object->GeneratedClass;
	}
}

void UGasCloud::ActivateAttack(FVector location, ABaseCharacter* target)
{
	time = cooldown;
	if (ABaseCharacter* character = dynamic_cast<ABaseCharacter*>(GetOwner()))
	{
		character->DecreaseMana(manaCost);
		FActorSpawnParameters SpawnParameters;
		ASpellEffect* BPProjectile = GetWorld()->SpawnActor<ASpellEffect>(blueprintReference, location, FRotator(0, 0, 0), SpawnParameters);
		BPProjectile->Initialize(character, this);
	}
}


