// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "Elevator.generated.h"

UCLASS()
class KILLLIGHT_API AElevator : public AActor
{
	GENERATED_BODY()
	
public:
	AElevator();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void StartOpen();

	UFUNCTION(BlueprintCallable)
	void StartClose();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Elevator")
	UStaticMeshComponent* Cage;

	UPROPERTY(VisibleAnywhere, Category = "Elevator")
	UStaticMeshComponent* Armature;

	UPROPERTY(VisibleAnywhere, Category = "Elevator")
	UStaticMeshComponent* LeftInteriorDoor;

	UPROPERTY(VisibleAnywhere, Category = "Elevator")
	UStaticMeshComponent* RightInteriorDoor;

	UPROPERTY(VisibleAnywhere, Category = "Elevator")
	UStaticMeshComponent* LeftOutsideDoor;

	UPROPERTY(VisibleAnywhere, Category = "Elevator")
	UStaticMeshComponent* RightOutsideDoor;

	/*
	* Open Door
	*/
	UPROPERTY(VisibleAnywhere)
	UTimelineComponent* OpenTimeline;
	FOnTimelineFloat OpenTrack;
	
	UPROPERTY(EditAnywhere, Category = "Curves")
	UCurveFloat* OpenCurve;

	float LeftOpenStartY;
	float RightOpenStartY;

	UPROPERTY(EditAnywhere)
	float OpenDeltaY;

	UFUNCTION()
	void Open(float OpenValue);
public:

};
