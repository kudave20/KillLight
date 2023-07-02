// Fill out your copyright notice in the Description page of Project Settings.


#include "TheKillLight.h"
#include "KillLight/Prop/Lamp.h"
#include "Components/SphereComponent.h"

ATheKillLight::ATheKillLight()
{
	PrimaryActorTick.bCanEverTick = false;

	OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
	OverlapSphere->SetupAttachment(GetMesh());
	OverlapSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
}

void ATheKillLight::BeginPlay()
{
	Super::BeginPlay();
	
	OverlapSphere->OnComponentBeginOverlap.AddDynamic(this, &ATheKillLight::OnOverlapBegin);
	OverlapSphere->OnComponentEndOverlap.AddDynamic(this, &ATheKillLight::OnOverlapEnd);
}

void ATheKillLight::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATheKillLight::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATheKillLight::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ALamp* Lamp = Cast<ALamp>(OtherActor);
	if (Lamp)
	{
		Lamp->TurnOff();
	}
}

void ATheKillLight::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ALamp* Lamp = Cast<ALamp>(OtherActor);
	if (Lamp)
	{
		Lamp->TurnOn();
	}
}

