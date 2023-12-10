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

	UPROPERTY(VisibleAnywhere, Category = "Door")
	TObjectPtr<USceneComponent> Root;
	
	UPROPERTY(VisibleAnywhere, Category = "Door")
	TObjectPtr<UStaticMeshComponent> DoorFrame;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Door")
	TObjectPtr<UStaticMeshComponent> Door;

public:

};
