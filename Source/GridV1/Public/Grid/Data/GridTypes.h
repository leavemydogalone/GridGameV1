// Copyright Leavemydogalone

#pragma once

#include "CoreMinimal.h"

// Will need to convert this to left/right verbiage
UENUM(BlueprintType)
enum class EHexDirection : uint8
{
	None		UMETA(DisplayName = "None"),
	Left		UMETA(DisplayName = "Left"),
	Right		UMETA(DisplayName = "Right"),
	UpRight		UMETA(DisplayName = "UpRight"),
	UpLeft		UMETA(DisplayName = "UpLeft"),
	DownRight	UMETA(DisplayName = "DownRight"),
	DownLeft	UMETA(DisplayName = "DownLeft"),
};
