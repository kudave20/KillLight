// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Door.h"
#include "LockedDoor.generated.h"

/**
 * 
 */
UCLASS()
class KILLLIGHT_API ALockedDoor : public ADoor
{
	GENERATED_BODY()
	
protected:
	virtual void OnInteract_Implementation() override;

private:
	UPROPERTY(EditAnywhere)
	class USoundCue* DoorSound;
};
