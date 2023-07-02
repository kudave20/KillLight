// Fill out your copyright notice in the Description page of Project Settings.


#include "Lamp.h"

ALamp::ALamp()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(Mesh);
}

void ALamp::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALamp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALamp::TurnOn()
{
	if (OnMaterial)
	{
		Mesh->SetMaterial(MaterialIndexToChange, OnMaterial);
	}
}

void ALamp::TurnOff()
{
	if (OffMaterial)
	{
		Mesh->SetMaterial(MaterialIndexToChange, OffMaterial);
	}
}
