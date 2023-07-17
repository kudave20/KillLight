// Fill out your copyright notice in the Description page of Project Settings.


#include "LCDLamp.h"
#include "Components/PointLightComponent.h"

ALCDLamp::ALCDLamp() : Super()
{
	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(RootComponent);
	PointLight->SetMobility(EComponentMobility::Stationary);
}

void ALCDLamp::TurnOff()
{
	Super::TurnOff();

	if (PointLight)
	{
		PointLight->SetVisibility(false);
	}
}
