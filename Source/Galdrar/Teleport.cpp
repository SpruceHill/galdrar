// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "Teleport.h"

UTeleport::UTeleport()
{
	name = "Teleport";
	desc = "Instantly appear at a different location.";
	activation = EActivation::TARGET_GROUND;
	spellTarget = ESpellTarget::CIRCLE;
	manaCost = 5.f;
	radius = 50.f;
	bProjectile = false;
	bDoesDamage = false;

	damage = 10.f;
	cooldown = 2.f;
	time = 0.f;
	damageType = EGaldrarDamageType::PHYSICAL;
	range = 600.f;

	// 2 = Spell, ID = 0006
	ID = 20006;
}

void UTeleport::ActivateAttack(FVector location, ABaseCharacter* target)
{
	time = cooldown;
	if (ABaseCharacter* character = dynamic_cast<ABaseCharacter*>(GetOwner()))
	{
		character->DecreaseMana(manaCost);
		
		FCollisionQueryParams TraceParams(FName(TEXT("VictoreCore Trace")), true, NULL);
		TraceParams.bTraceComplex = true;
		TraceParams.AddIgnoredActor(character);
		FHitResult HitOut = FHitResult(ForceInit);
		FVector start = location;
		start.Z += 200;
		FVector end = location;
		end.Z -= 300;
		ECollisionChannel CollisionChannel = ECC_WorldStatic;
		GetWorld()->LineTraceSingle(HitOut, start, end, CollisionChannel, TraceParams);

		FVector result = HitOut.Location;
		FVector forward = character->GetActorForwardVector();
		
		if (ABaseCharacter* character2 = dynamic_cast<ABaseCharacter*>(HitOut.GetActor()))
		{
			result.X += 100.f;
			result.Z -= character2->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
			character->TeleportTo(result, character->GetActorRotation(), false, false);
		}
		else
		{
			result.Z += character->GetCapsuleComponent()->GetScaledCapsuleHalfHeight();
			character->SetActorLocation(result);
		}
		character->SetActorRotation(forward.Rotation());
	}
}

