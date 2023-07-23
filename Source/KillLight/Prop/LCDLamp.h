// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Lamp.h"
#include "LCDLamp.generated.h"

/**
 * 
 */
UCLASS()
class KILLLIGHT_API ALCDLamp : public ALamp
{
	GENERATED_BODY()

public:
	ALCDLamp();

	virtual void TurnOff() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UPointLightComponent* PointLight;

	UPROPERTY(EditAnywhere, Category = "Sound")
	class USoundCue* LightOutSound;
};
