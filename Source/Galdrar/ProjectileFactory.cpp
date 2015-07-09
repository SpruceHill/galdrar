// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "ProjectileFactory.h"
#include "BaseProjectile.h"
#include "SpellEffect.h"

void UProjectileFactory::SpawnAttackEffect(UWorld* world, ABaseCharacter* attacker, FVector targetLocation, Attack* attack)
{
	Spell* spell = (Spell*)attack;
	if (spell)
	{
		if (spell->IsProjectile())
		{
			UProjectileFactory::SpawnProjectile(world, attacker, targetLocation, spell);
		}
		else
		{
			FActorSpawnParameters SpawnParameters;
			ASpellEffect* base = world->SpawnActor<ASpellEffect>(ASpellEffect::StaticClass(), attacker->GetActorLocation(), attacker->GetActorForwardVector().Rotation(), SpawnParameters);
			ASpellEffect* blueprintSpellEffect = NULL;
		
			switch (spell->GetSpellType())
			{
			case Spell::SpellType::GAS_CLOUD:
				blueprintSpellEffect = world->SpawnActor<ASpellEffect>(base->GasCloudBluePrintReference, targetLocation, FRotator(0, 0, 0), SpawnParameters);
				break;
			}

			base->Destroy();
			if (blueprintSpellEffect)
			{
				blueprintSpellEffect->Initialize(attacker, attack);
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "SpellEffect Spawn Failed");
			}
		}
	}
}

void UProjectileFactory::SpawnProjectile(UWorld* world, ABaseCharacter* attacker, FVector targetLocation, Attack* attack)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.bNoCollisionFail = true; //TODO: NOW WORKING
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
		case Spell::SpellType::LIGHNING_BOLT:
			BPProjectile = world->SpawnActor<ABaseProjectile>(base->LightningBoltBluePrintReference, attacker->GetActorLocation(), attacker->GetActorForwardVector().Rotation(), SpawnParameters);
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
