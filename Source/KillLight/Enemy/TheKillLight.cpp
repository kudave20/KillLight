// Fill out your copyright notice in the Description page of Project Settings.


#include "TheKillLight.h"
#include "KillLight/Prop/Lamp.h"
#include "Components/SphereComponent.h"
#include "Components/BoxComponent.h"
#include "KillLight/Character/MainCharacter.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"

ATheKillLight::ATheKillLight()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GetCapsuleComponent()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
	OverlapSphere->SetupAttachment(RootComponent);
	OverlapSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	OverlapSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);

	CautionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CautionBox"));
	CautionBox->SetupAttachment(RootComponent);
	CautionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CautionBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CautionBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	CautionBox->SetGenerateOverlapEvents(false);
}

void ATheKillLight::BeginPlay()
{
	Super::BeginPlay();
	
	OverlapSphere->OnComponentBeginOverlap.AddDynamic(this, &ATheKillLight::OnSphereBeginOverlap);
	//OverlapSphere->OnComponentEndOverlap.AddDynamic(this, &ATheKillLight::OnSphereEndOverlap);

	CautionBox->OnComponentBeginOverlap.AddDynamic(this, &ATheKillLight::OnCautionBoxBeginOverlap);
	CautionBox->OnComponentEndOverlap.AddDynamic(this, &ATheKillLight::OnCautionBoxEndOverlap);
}

void ATheKillLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATheKillLight::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATheKillLight::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ALamp* Lamp = Cast<ALamp>(OtherActor);
	if (Lamp)
	{
		Lamp->TurnOff();
	}
}

/*void ATheKillLight::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ALamp* Lamp = Cast<ALamp>(OtherActor);
	if (Lamp)
	{
		Lamp->TurnOn();
	}
}*/

void ATheKillLight::OnCautionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
	if (MainCharacter)
	{
		MainCharacter->GetCautious();
	}
}

void ATheKillLight::OnCautionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
	if (MainCharacter)
	{
		MainCharacter->GetRelieved();
	}
}
