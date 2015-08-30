// Copyright Spruce Hill, All rights reserved.

#include "Galdrar.h"
#include "HeroCharacter.h"
#include "StandardBloodVial.h"
#include "Sword.h"
#include "DragonsBreath.h"
#include "GasCloud.h"
#include "Heal.h"
#include "Teleport.h"
#include "LightningBolt.h"
#include "Javelin.h"

AHeroCharacter::AHeroCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	name = "Hero";
	stats = CreateDefaultSubobject<UCharacterStatsComponent>(TEXT("Stats"));
	weapon = CreateDefaultSubobject<USword>(TEXT("Sword"));

	spell1 = CreateDefaultSubobject<UDragonsBreath>(TEXT("Dragons"));
	spell2 = CreateDefaultSubobject<UGasCloud>(TEXT("Gas"));
	spell3 = CreateDefaultSubobject<UHeal>(TEXT("Heal"));
	spell4 = CreateDefaultSubobject<UJavelin>(TEXT("Javelin"));


	bloodVialComponent = CreateDefaultSubobject<UStandardBloodVial>(TEXT("BloodVial"));
	
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

	CursorHitbox = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CursorHitbox"));
	CursorHitbox->SetCollisionProfileName(TEXT("UI"));
	CursorHitbox->AttachParent = RootComponent;
}

void AHeroCharacter::Zoom(float delta)
{
	CameraBoom->TargetArmLength += delta;
}

void AHeroCharacter::AddValuable(AValuable* valuable)
{
	HUDAdapter HA;
	HA.CreateDamageIndicator(this, "+" + FString::FromInt(valuable->GetValue()), UGaldrarColor::GetGoldColor(), false);
	lootValue += valuable->GetValue();
	valuable->OnPickup();
}

void AHeroCharacter::RemoveLootValue(int32 amount)
{
	if (lootValue - amount < 0) lootValue = 0;
	else lootValue -= amount;
}

int32 AHeroCharacter::GetLootValue()
{
	return lootValue;
}

ALoot* AHeroCharacter::GetInventory(int32 index)
{
	if (index == 0)
	{
		return inventorySlot1;
	}
	else if (index == 1)
	{
		return inventorySlot2;
	}
	else if (index == 2)
	{
		return inventorySlot3;
	}
	else if (index == 3)
	{
		return inventorySlot4;
	}
	else if (index == 4)
	{
		return inventorySlot5;
	}
	else
	{
		return inventorySlot6;
	}
}

UBloodVialComponent* AHeroCharacter::GetBloodVial()
{
	return bloodVialComponent;
}

int32 AHeroCharacter::GetBloodVialID()
{
	return bloodVialComponent->GetID();
}
int32 AHeroCharacter::GetBloodVialMaxCharges()
{
	return bloodVialComponent->GetMaxCharges();
}
int32 AHeroCharacter::GetBloodVialCharges()
{
	return bloodVialComponent->GetCharges();
}

void AHeroCharacter::AddBloodVialCharges(int32 nbrOfCharges)
{
	bloodVialComponent->AddCharges(nbrOfCharges);
}
