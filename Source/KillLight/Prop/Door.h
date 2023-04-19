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
	virtual void OnInteract_Implementation() override;

private:
	UPROPERTY(EditAnywhere, Category = "Door")
	UStaticMeshComponent* DoorFrame;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Door", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Door;

public:

};
