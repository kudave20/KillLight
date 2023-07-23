// Fill out your copyright notice in the Description page of Project Settings.


#include "LCDLamp.h"
#include "Components/PointLightComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

ALCDLamp::ALCDLamp() : Super()
{
	PointLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(RootComponent);
	PointLight->SetMobility(EComponentMobility::Stationary);
	PointLight->Intensity = 1000.0f;
	PointLight->LightColor = FColor(255, 241, 196);
	PointLight->AttenuationRadius = 600.0f;
}

void ALCDLamp::TurnOff()
{
	Super::TurnOff();

	if (PointLight)
	{
		PointLight->SetVisibility(false);
	}
	if (LightOutSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, LightOutSound, GetActorLocation());
	}
}
