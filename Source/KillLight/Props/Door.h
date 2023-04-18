// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KillLight/Interface/InteractInterface.h"
#include "Door.generated.h"

UCLASS()
class KILLLIGHT_API ADoor : public AActor, public IInteractInterface
{
	GENERATED_BODY()

public:
	ADoor();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void OnInteract_Implementation(AActor* InteractableActor) override;

private:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* DoorFrame;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Door;

	UPROPERTY(EditAnywhere)
	class USoundCue* DoorSound;

public:

};
