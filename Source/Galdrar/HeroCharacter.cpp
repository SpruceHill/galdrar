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
#include "AngerManagement.h"
#include "Berserker.h"
#include "Hardened.h"
#include "HotHeaded.h"

AHeroCharacter::AHeroCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	name = "Hero";
	stats = CreateDefaultSubobject<UCharacterStatsComponent>(TEXT("Stats"));
	
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

void AHeroCharacter::InitializeHero(
	TSubclassOf<UBaseWeapon> MainWeapon,
	TSubclassOf<UBaseSpell> NewSpell1,
	TSubclassOf<UBaseSpell> NewSpell2,
	TSubclassOf<UBaseSpell> NewSpell3,
	TSubclassOf<UBaseSpell> NewSpell4,
	TSubclassOf<UBaseTrait> NewTrait1,
	TSubclassOf<UBaseTrait> NewTrait2,
	TSubclassOf<UBloodVialComponent> NewBloodVial
	)
{
	// WEAPONS
	if (MainWeapon->IsChildOf(USword::StaticClass())) weapon = NewObject<USword>(this);

	// TODO: SHould work
	// Read https://wiki.unrealengine.com/Blueprint_Node:_Create_Object_from_Blueprint
	//spell1 = Cast<UBaseSpell>(NewObject<UObject>(NewSpell1));
	//spell1 = NewObject<UBaseSpell>(NewSpell1);
	
	
	// SPELL 1
	if (NewSpell1->IsChildOf(UDragonsBreath::StaticClass())) spell1 = NewObject<UDragonsBreath>(this);
	else if (NewSpell1->IsChildOf(UGasCloud::StaticClass())) spell1 = NewObject<UGasCloud>(this);
	else if (NewSpell1->IsChildOf(UHeal::StaticClass())) spell1 = NewObject<UHeal>(this);
	else if (NewSpell1->IsChildOf(UJavelin::StaticClass())) spell1 = NewObject<UJavelin>(this);
	else if (NewSpell1->IsChildOf(ULightningBolt::StaticClass())) spell1 = NewObject<ULightningBolt>(this);
	else if (NewSpell1->IsChildOf(UTeleport::StaticClass())) spell1 = NewObject<UTeleport>(this);
	
	// SPELL 2
	if (NewSpell2->IsChildOf(UDragonsBreath::StaticClass())) spell2 = NewObject<UDragonsBreath>(this);
	else if (NewSpell2->IsChildOf(UGasCloud::StaticClass())) spell2 = NewObject<UGasCloud>(this);
	else if (NewSpell2->IsChildOf(UHeal::StaticClass())) spell2 = NewObject<UHeal>(this);
	else if (NewSpell2->IsChildOf(UJavelin::StaticClass())) spell2 = NewObject<UJavelin>(this);
	else if (NewSpell2->IsChildOf(ULightningBolt::StaticClass())) spell2 = NewObject<ULightningBolt>(this);
	else if (NewSpell2->IsChildOf(UTeleport::StaticClass())) spell2 = NewObject<UTeleport>(this);

	// SPELL 3
	if (NewSpell3->IsChildOf(UDragonsBreath::StaticClass())) spell3 = NewObject<UDragonsBreath>(this);
	else if (NewSpell3->IsChildOf(UGasCloud::StaticClass())) spell3 = NewObject<UGasCloud>(this);
	else if (NewSpell3->IsChildOf(UHeal::StaticClass())) spell3 = NewObject<UHeal>(this);
	else if (NewSpell3->IsChildOf(UJavelin::StaticClass())) spell3 = NewObject<UJavelin>(this);
	else if (NewSpell3->IsChildOf(ULightningBolt::StaticClass())) spell3 = NewObject<ULightningBolt>(this);
	else if (NewSpell3->IsChildOf(UTeleport::StaticClass())) spell3 = NewObject<UTeleport>(this);

	// SPELL 4
	if (NewSpell4->IsChildOf(UDragonsBreath::StaticClass())) spell4 = NewObject<UDragonsBreath>(this);
	else if (NewSpell4->IsChildOf(UGasCloud::StaticClass())) spell4 = NewObject<UGasCloud>(this);
	else if (NewSpell4->IsChildOf(UHeal::StaticClass())) spell4 = NewObject<UHeal>(this);
	else if (NewSpell4->IsChildOf(UJavelin::StaticClass())) spell4 = NewObject<UJavelin>(this);
	else if (NewSpell4->IsChildOf(ULightningBolt::StaticClass())) spell4 = NewObject<ULightningBolt>(this);
	else if (NewSpell4->IsChildOf(UTeleport::StaticClass())) spell4 = NewObject<UTeleport>(this);

	// TRAIT 1
	if (NewTrait1->IsChildOf(UAngerManagement::StaticClass())) trait1 = NewObject<UAngerManagement>(this);
	else if (NewTrait1->IsChildOf(UBerserker::StaticClass())) trait1 = NewObject<UBerserker>(this);
	else if (NewTrait1->IsChildOf(UHardened::StaticClass())) trait1 = NewObject<UHardened>(this);
	else if (NewTrait1->IsChildOf(UHotHeaded::StaticClass())) trait1 = NewObject<UHotHeaded>(this);

	// TRAIT 2
	if (NewTrait2->IsChildOf(UAngerManagement::StaticClass())) trait2 = NewObject<UAngerManagement>(this);
	else if (NewTrait2->IsChildOf(UBerserker::StaticClass())) trait2 = NewObject<UBerserker>(this);
	else if (NewTrait2->IsChildOf(UHardened::StaticClass())) trait2 = NewObject<UHardened>(this);
	else if (NewTrait2->IsChildOf(UHotHeaded::StaticClass())) trait2 = NewObject<UHotHeaded>(this);

	// Blood Vial
	if (NewBloodVial->IsChildOf(UStandardBloodVial::StaticClass())) bloodVialComponent = NewObject<UStandardBloodVial>(this);

	// REGISTER COMPONENTS
	AddInstanceComponent(weapon);
	AddInstanceComponent(spell1);
	AddInstanceComponent(spell2);
	AddInstanceComponent(spell3);
	AddInstanceComponent(spell4);
	AddInstanceComponent(trait1);
	AddInstanceComponent(trait2);
	AddInstanceComponent(bloodVialComponent);
	
	weapon->RegisterComponent();
	spell1->RegisterComponent();
	spell2->RegisterComponent();
	spell3->RegisterComponent();
	spell4->RegisterComponent();
	trait1->RegisterComponent();
	trait2->RegisterComponent();
	bloodVialComponent->RegisterComponent();

	stats->movementSpeed -= weapon->GetWeight();
	stats->defaultMovementSpeed -= weapon->GetWeight();
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
	stats->movementSpeed -= valuable->GetValue();
	valuable->OnPickup();
}

void AHeroCharacter::RemoveLootValue(int32 amount)
{
	if (lootValue - amount < 0)
	{
		stats->movementSpeed += (amount - lootValue);
		lootValue = 0;
	}
	else
	{
		stats->movementSpeed += amount;
		lootValue -= amount;
	}
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
