// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Lamp.generated.h"

UCLASS()
class KILLLIGHT_API ALamp : public AActor
{
	GENERATED_BODY()
	
public:
	ALamp();
	virtual void Tick(float DeltaTime) override;

	virtual void TurnOn();
	virtual void TurnOff();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Material")
	UMaterialInstance* OnMaterial;

	UPROPERTY(EditAnywhere, Category = "Material")
	UMaterialInstance* OffMaterial;

	UPROPERTY(EditAnywhere, Category = "Material")
	int32 MaterialIndexToChange;

public:

};
