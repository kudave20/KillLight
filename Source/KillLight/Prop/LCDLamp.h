// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Lamp.h"
#include "LCDLamp.generated.h"

class UPointLightComponent;
class USoundCue;

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPointLightComponent> PointLight;

	UPROPERTY(EditAnywhere, Category = "Sound")
	TObjectPtr<USoundCue> LightOutSound;
};
