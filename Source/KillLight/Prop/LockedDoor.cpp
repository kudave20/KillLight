// Fill out your copyright notice in the Description page of Project Settings.


#include "LockedDoor.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

void ALockedDoor::OnInteract_Implementation()
{
	Super::OnInteract_Implementation();

	UGameplayStatics::PlaySoundAtLocation(this, DoorSound, GetActorLocation());
}