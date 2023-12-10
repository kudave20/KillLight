// Fill out your copyright notice in the Description page of Project Settings.


#include "UnlockedDoor.h"
#include "GeometryCollection/GeometryCollectionComponent.h"

AUnlockedDoor::AUnlockedDoor()
{
	DoorGeometryCollection = CreateDefaultSubobject<UGeometryCollectionComponent>(TEXT("DoorGeometryCollection"));
	DoorGeometryCollection->SetupAttachment(Root);
	DoorGeometryCollection->SetVisibility(false);
	DoorGeometryCollection->SetSimulatePhysics(false);
}

void AUnlockedDoor::DestroyDoor_Implementation()
{
	if (Door)
	{
		Door->SetVisibility(false);
	}
	if (DoorGeometryCollection)
	{
		DoorGeometryCollection->SetVisibility(true);
		DoorGeometryCollection->SetSimulatePhysics(true);
	}
}
