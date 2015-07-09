// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "BaseCharacter.h"
#include "Attack.h"
#include "SpellEffect.generated.h"

UCLASS()
class GALDRAR_API ASpellEffect : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpellEffect();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void Initialize(ABaseCharacter* caster, Attack* attack);

	UFUNCTION(BlueprintCallable, Category = SpellEffect)
	void Trigger(AActor* actor);

	TSubclassOf<class ASpellEffect> GasCloudBluePrintReference;

	TSubclassOf<class ABaseProjectile> DragonsBreathBluePrintReference;
	TSubclassOf<class ABaseProjectile> JavelinBluePrintReference;
	TSubclassOf<class ABaseProjectile> LightningBoltBluePrintReference;

	UPROPERTY(BlueprintReadOnly, Category = SpellEffect)
	float time;

	ABaseCharacter* caster;
	Attack* attack;
};
