// Fill out your copyright notice in the Description page of Project Settings.


#include "Elevator.h"

AElevator::AElevator()
{
	PrimaryActorTick.bCanEverTick = false;

	Cage = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cage"));
	SetRootComponent(Cage);

	Armature = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Armature"));
	Armature->SetupAttachment(Cage);

	LeftInteriorDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftInteriorDoor"));
	LeftInteriorDoor->SetupAttachment(Armature);

	RightInteriorDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightInteriorDoor"));
	RightInteriorDoor->SetupAttachment(Armature);
	
	LeftOutsideDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftOutsideDoor"));
	LeftOutsideDoor->SetupAttachment(Armature);
	
	RightOutsideDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightOutsideDoor"));
	RightOutsideDoor->SetupAttachment(Armature);

	OpenTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("OpenTimeline"));

	SetActorEnableCollision(false);
}

void AElevator::BeginPlay()
{
	Super::BeginPlay();
	
}

void AElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AElevator::StartOpen()
{
	OpenTrack.BindDynamic(this, &AElevator::Open);
	if (OpenCurve && OpenTimeline)
	{
		LeftOpenStartY = LeftInteriorDoor->GetComponentLocation().Y;
		RightOpenStartY = RightInteriorDoor->GetComponentLocation().Y;
		OpenTimeline->AddInterpFloat(OpenCurve, OpenTrack);
		OpenTimeline->Play();
	}
}

void AElevator::Open(float OpenValue)
{
	if (LeftInteriorDoor == nullptr || RightInteriorDoor == nullptr || LeftOutsideDoor == nullptr || RightOutsideDoor == nullptr) return;

	float LeftOpenCurrentY = FMath::Lerp(LeftOpenStartY, LeftOpenStartY - OpenDeltaY, OpenValue);
	float RightOpenCurrentY = FMath::Lerp(RightOpenStartY, RightOpenStartY + OpenDeltaY, OpenValue);

	FVector Location = LeftInteriorDoor->GetComponentLocation();
	Location.Y = LeftOpenCurrentY;
	LeftInteriorDoor->SetWorldLocation(Location);

	Location = LeftOutsideDoor->GetComponentLocation();
	Location.Y = LeftOpenCurrentY;
	LeftOutsideDoor->SetWorldLocation(Location);

	Location = RightInteriorDoor->GetComponentLocation();
	Location.Y = RightOpenCurrentY;
	RightInteriorDoor->SetWorldLocation(Location);

	Location = RightOutsideDoor->GetComponentLocation();
	Location.Y = RightOpenCurrentY;
	RightOutsideDoor->SetWorldLocation(Location);
}

void AElevator::StartClose()
{
	if (OpenCurve && OpenTimeline)
	{
		OpenTimeline->Reverse();
	}
}

