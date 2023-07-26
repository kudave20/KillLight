// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "KillLight/Interface/InteractInterface.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/PostProcessComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SpotLightComponent.h"
#include "Sound/SoundCue.h"

AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetMesh(), FName("head"));
	Camera->bUsePawnControlRotation = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 0.0f;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraRotationLag = true;

	FlashLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("FlashLight"));
	FlashLight->SetupAttachment(SpringArm);
	FlashLight->LightColor = FColor(255, 251, 228);
	FlashLight->AttenuationRadius = 1260.0f;
	FlashLight->InnerConeAngle = 11.75f;
	FlashLight->OuterConeAngle = 32.0f;
	FlashLight->SetVisibility(false);

	PostProcess = CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcess"));
	PostProcess->SetupAttachment(Camera);
	PostProcess->bEnabled = false;
	PostProcess->Settings.VignetteIntensity = 0.8f;
	PostProcess->Settings.bOverride_VignetteIntensity = true;
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MainContext, 0);
		}
	}
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &AMainCharacter::Move);
		//EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Completed, this, &AMainCharacter::StopHeadBob);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainCharacter::Look);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AMainCharacter::Interact);
		EnhancedInputComponent->BindAction(ToggleFlashAction, ETriggerEvent::Triggered, this, &AMainCharacter::ToggleFlash);
	}
}

void AMainCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MovementVector.Y);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, MovementVector.X);

	//StartHeadBob();
}

/*
void AMainCharacter::StartHeadBob()
{
	PlayerCameraManager = PlayerCameraManager == nullptr ? UGameplayStatics::GetPlayerCameraManager(this, 0) : PlayerCameraManager;
	if (PlayerCameraManager == nullptr) return;

	if (!bShakeEnabled)
	{
		WalkCameraShake = PlayerCameraManager->StartCameraShake(WalkCameraShakeClass);
		bShakeEnabled = true;
	}
}

void AMainCharacter::StopHeadBob()
{
	PlayerCameraManager = PlayerCameraManager == nullptr ? UGameplayStatics::GetPlayerCameraManager(this, 0) : PlayerCameraManager;
	if (PlayerCameraManager == nullptr) return;

	if (bShakeEnabled && WalkCameraShake)
	{
		PlayerCameraManager->StopCameraShake(WalkCameraShake);
		bShakeEnabled = false;
	}
}
*/

void AMainCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);
}

void AMainCharacter::Interact()
{
	FHitResult HitResult;
	FVector Start = Camera->GetComponentLocation();
	FVector End = Start + Camera->GetComponentRotation().Vector() * ArmLength;
	GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECollisionChannel::ECC_Visibility
	);

	AActor* Interactable = HitResult.GetActor();
	if (Interactable && Interactable->Implements<UInteractInterface>())
	{
		IInteractInterface::Execute_OnInteract(Interactable);
	}
}

void AMainCharacter::ToggleFlash()
{
	if (FlashLight)
	{
		if (FlashLight->IsVisible())
		{
			UGameplayStatics::PlaySoundAtLocation(this, FlashOffSound, FlashLight->GetComponentLocation());
		}
		else
		{
			UGameplayStatics::PlaySoundAtLocation(this, FlashOnSound, FlashLight->GetComponentLocation());
		}
		FlashLight->ToggleVisibility();
	}
}

void AMainCharacter::GetCautious()
{
	if (PostProcess)
	{
		PostProcess->bEnabled = true;
	}
}

void AMainCharacter::GetRelieved()
{
	if (PostProcess)
	{
		PostProcess->bEnabled = false;
	}
}
