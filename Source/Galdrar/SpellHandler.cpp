// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "SpellHandler.h"
#include "ProjectileFactory.h"

// Target unit
void SpellHandler::ActivateSpell(UAttackComponent* attack, ABaseCharacter* caster, ABaseCharacter* target)
{
	/*attack->Activate();
	Spell* spell = (Spell*)attack;
	switch (spell->GetSpellType())
	{
	case Spell::SpellType::HEAL: 
		target->Heal(spell->GetDamage());
		break;
	}*/
}
// Target ground
void SpellHandler::ActivateSpell(UAttackComponent* attack, UWorld* world, FVector location, ABaseCharacter* caster)
{
	/*attack->Activate();
	//Spell* spell = (Spell*)attack;
	caster->DecreaseMana(attack->GetManaCost());
	switch (spell->GetSpellType())
	{
	case Spell::SpellType::DRAGONS_BREATH: 
		UProjectileFactory::SpawnAttackEffect(world, caster, location, attack); 
		break;
	case Spell::SpellType::JAVELIN: 
		UProjectileFactory::SpawnAttackEffect(world, caster, location, attack);
		break;
	case Spell::SpellType::GAS_CLOUD: 
		UProjectileFactory::SpawnAttackEffect(world, caster, location, attack); 
		break;
	case Spell::SpellType::LIGHNING_BOLT: 
		UProjectileFactory::SpawnAttackEffect(world, caster, location, attack); 
		break;
	case Spell::SpellType::TELEPORT:
		
		FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true, NULL);
		TraceParams.bTraceComplex = true;
		TraceParams.AddIgnoredActor(caster);
		FHitResult HitOut = FHitResult(ForceInit);
		FVector start = location;
		start.Z += 200;
		FVector end = location;
		end.Z -= 300;
		ECollisionChannel CollisionChannel = ECC_WorldStatic;
		world->LineTraceSingle(HitOut, start, end, CollisionChannel, TraceParams);

		FVector result = HitOut.Location;
		FVector forward = caster->GetActorForwardVector();
		if (ABaseCharacter* character = dynamic_cast<ABaseCharacter*>(HitOut.GetActor()))
		{
			result.X += 100.f;
			result.Z -= character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
			caster->TeleportTo(result, caster->GetActorRotation(), false, false);
		}
		else
		{
			result.Z += caster->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
			caster->SetActorLocation(result);
		}
		caster->SetActorRotation(forward.Rotation());
		break;
	}*/
}
// Self
void SpellHandler::ActivateSpell(UAttackComponent* attack, ABaseCharacter* caster)
{
	attack->ActivateAttack(FVector::ZeroVector, NULL);
}