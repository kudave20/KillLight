// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ELevelIndex : uint8
{
	ELI_First UMETA(DisplayName = "First"),
	ELI_Second UMETA(DisplayName = "Second"),

	ELI_MAX UMETA(DisplayName = "Default MAX")
};

