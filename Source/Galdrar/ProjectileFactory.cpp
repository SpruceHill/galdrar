// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "ProjectileFactory.h"
#include "BaseProjectile.h"

void UProjectileFactory::SpawnAttackEffect(UWorld* world, ABaseCharacter* attacker, FVector targetLocation, Attack* attack)
{
	Spell* spell = (Spell*)attack;
	if (spell)
	{
		switch (spell->GetSpellType())
		{
		case Spell::SpellType::DRAGONS_BREATH : UProjectileFactory::SpawnProjectile(world, attacker, targetLocation, spell); break;
		case Spell::SpellType::GAS_CLOUD : return;
		case Spell::SpellType::LIGHNING_BOLT : return;
		case Spell::SpellType::JAVELIN: UProjectileFactory::SpawnProjectile(world, attacker, targetLocation, spell); break;
		}
	}
}

void UProjectileFactory::SpawnProjectile(UWorld* world, ABaseCharacter* attacker, FVector targetLocation, Attack* attack)
{
	FActorSpawnParameters SpawnParameters;
	ABaseProjectile* base = world->SpawnActor<ABaseProjectile>(ABaseProjectile::StaticClass(), attacker->GetActorLocation(), attacker->GetActorForwardVector().Rotation(), SpawnParameters);
	ABaseProjectile* BPProjectile = NULL;
	Spell* spell = (Spell*)attack;
	if (spell)
	{
		// All spell projectiles must be listed here
		switch (spell->GetSpellType())
		{
		case Spell::SpellType::DRAGONS_BREATH: 
			BPProjectile = world->SpawnActor<ABaseProjectile>(base->DragonsBreathBluePrintReference, attacker->GetActorLocation(), attacker->GetActorForwardVector().Rotation(), SpawnParameters);
			break;
		case Spell::SpellType::JAVELIN:
			BPProjectile = world->SpawnActor<ABaseProjectile>(base->JavelinBluePrintReference, attacker->GetActorLocation(), attacker->GetActorForwardVector().Rotation(), SpawnParameters);
			break;
		}
	}
	base->Destroy();
	if (BPProjectile)
	{
		BPProjectile->Initialize(attacker, attack);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Projectile Spawn Failed");
	}
}
