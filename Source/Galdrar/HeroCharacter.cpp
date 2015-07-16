// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "HeroCharacter.h"
#include "Attack.h"
#include "Sword.h"
#include "DamageType.h"
#include "BurnEffect.h"
#include "EffectType.h"
#include "DragonsBreath.h"
#include "GasCloud.h"
#include "LightningBolt.h"
#include "Heal.h"
#include "Javelin.h"
#include "Teleport.h"

AHeroCharacter::AHeroCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	name = "Hero";
	stats = new CharacterStats();
	weapon = new Sword();
	//inventory.Init(NULL, 5);
	spells[0] = new DragonsBreath();
	spells[1] = new GasCloud();
	spells[2] = new Javelin();
	spells[3] = new Teleport();
	this->GetMesh()->bReceivesDecals = false;

	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 1000.f;
	CameraBoom->RelativeRotation = FRotator(-45.f, 45.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 5.f;

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}

void AHeroCharacter::Zoom(float delta)
{
	CameraBoom->TargetArmLength += delta;
}

int32 AHeroCharacter::GetSpellIdAtIndex(int32 index)
{
	return spells[index]->GetID();
}

float AHeroCharacter::GetSpellCooldownAtIndex(int32 index)
{
	return spells[index]->GetCooldown();
}

float AHeroCharacter::GetSpellTimeAtIndex(int32 index)
{
	return spells[index]->GetTime();
}

FString AHeroCharacter::GetSpellNameAtIndex(int32 index)
{
	return spells[index]->GetName();
}

FString AHeroCharacter::GetSpellDescAtIndex(int32 index)
{
	return spells[index]->GetDesc();
}


TArray<ALoot*> AHeroCharacter::GetInventory()
{
	return inventory;
}
