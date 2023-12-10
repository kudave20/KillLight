// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Door.h"
#include "UnlockedDoor.generated.h"

class UGeometryCollectionComponent;

/**
 * 
 */
UCLASS()
class KILLLIGHT_API AUnlockedDoor : public ADoor
{
	GENERATED_BODY()

public:
	AUnlockedDoor();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DestroyDoor();
	virtual void DestroyDoor_Implementation();
	
private:
	UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bIsOpen;

	UPROPERTY(VisibleAnywhere, Category = "Door")
	TObjectPtr<UGeometryCollectionComponent> DoorGeometryCollection;
};
