// Copyright Spruce Hill, All rights reserved.

#pragma once

#include "GameFramework/Actor.h"
#include "BaseInteractable.generated.h"

UCLASS()
class GALDRAR_API ABaseInteractable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseInteractable();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintImplementableEvent, Category = Interactable)
	void Interact(ABaseCharacter* interactee);

	UFUNCTION(BlueprintCallable, Category = Interactable)
	FString GetName();
	UFUNCTION(BlueprintCallable, Category = Interactable)
	FString GetDesc();

	UFUNCTION(BlueprintCallable, Category = Interactable)
	UPrimitiveComponent* GetMesh();

	UFUNCTION(BlueprintCallable, Category = Interactable)
	void SetMesh(UPrimitiveComponent* newMesh);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CharacterStats)
	bool active = true;

protected:
	UPROPERTY(BlueprintReadWrite, Category = Interactable)
	FString name;
	UPROPERTY(BlueprintReadWrite, Category = Interactable)
	FString desc;
	UPROPERTY(BlueprintReadWrite, Category = Interactable)
	UPrimitiveComponent* mesh;
	
};
