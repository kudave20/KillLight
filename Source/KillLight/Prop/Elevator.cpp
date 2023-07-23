// Fill out your copyright notice in the Description page of Project Settings.


#include "Elevator.h"

AElevator::AElevator()
{
	PrimaryActorTick.bCanEverTick = false;

	Cage = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cage"));
	SetRootComponent(Cage);
	Cage->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Armature = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Armature"));
	Armature->SetupAttachment(Cage);
	Armature->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	LeftInteriorDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftInteriorDoor"));
	LeftInteriorDoor->SetupAttachment(Armature);

	RightInteriorDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightInteriorDoor"));
	RightInteriorDoor->SetupAttachment(Armature);
	
	LeftOutsideDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LeftOutsideDoor"));
	LeftOutsideDoor->SetupAttachment(Armature);
	
	RightOutsideDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RightOutsideDoor"));
	RightOutsideDoor->SetupAttachment(Armature);

	OpenTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("OpenTimeline"));
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
		LeftOpenStartY = LeftInteriorDoor->GetRelativeLocation().Y;
		RightOpenStartY = RightInteriorDoor->GetRelativeLocation().Y;
		OpenTimeline->AddInterpFloat(OpenCurve, OpenTrack);
		OpenTimeline->Play();
	}
}

void AElevator::Open(float OpenValue)
{
	if (LeftInteriorDoor == nullptr || RightInteriorDoor == nullptr || LeftOutsideDoor == nullptr || RightOutsideDoor == nullptr) return;

	float LeftOpenCurrentY = FMath::Lerp(LeftOpenStartY, LeftOpenStartY - OpenDeltaY, OpenValue);
	float RightOpenCurrentY = FMath::Lerp(RightOpenStartY, RightOpenStartY + OpenDeltaY, OpenValue);

	FVector Location = LeftInteriorDoor->GetRelativeLocation();
	Location.Y = LeftOpenCurrentY;
	LeftInteriorDoor->SetRelativeLocation(Location);

	Location = LeftOutsideDoor->GetRelativeLocation();
	Location.Y = LeftOpenCurrentY;
	LeftOutsideDoor->SetRelativeLocation(Location);

	Location = RightInteriorDoor->GetRelativeLocation();
	Location.Y = RightOpenCurrentY;
	RightInteriorDoor->SetRelativeLocation(Location);

	Location = RightOutsideDoor->GetRelativeLocation();
	Location.Y = RightOpenCurrentY;
	RightOutsideDoor->SetRelativeLocation(Location);
}

void AElevator::StartClose()
{
	if (OpenCurve && OpenTimeline)
	{
		OpenTimeline->Reverse();
	}
}

