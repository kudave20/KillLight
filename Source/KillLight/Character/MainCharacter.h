// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MainCharacter.generated.h"

UCLASS()
class KILLLIGHT_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMainCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void GetCautious();
	void GetRelieved();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputMappingContext* MainContext;

	UPROPERTY(EditAnywhere, Category = Input)
	class UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* ToggleFlashAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Interact();
	void ToggleFlash();

private:
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpotLightComponent* FlashLight;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UPostProcessComponent* PostProcess;

	UPROPERTY(EditAnywhere, Category = "Length")
	float ArmLength = 200.0f;

	/*UPROPERTY()
	APlayerCameraManager* PlayerCameraManager;

	UPROPERTY(EditAnywhere, Category = "Camera Shake")
	TSubclassOf<UCameraShakeBase> WalkCameraShakeClass;

	UPROPERTY()
	UCameraShakeBase* WalkCameraShake;

	bool bShakeEnabled;

	void StartHeadBob();
	void StopHeadBob();
	*/

	UPROPERTY(EditAnywhere, Category = "Sound")
	class USoundCue* FlashOnSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundCue* FlashOffSound;

public:

};
