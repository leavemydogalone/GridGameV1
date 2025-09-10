// Copyright Leavemydogalone

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EHexDirection : uint8
{
	None      UMETA(DisplayName = "None"),
	East      UMETA(DisplayName = "East"),
	West      UMETA(DisplayName = "West"),
	Northeast UMETA(DisplayName = "Northeast"),
	Northwest UMETA(DisplayName = "Northwest"),
	Southeast UMETA(DisplayName = "Southeast"),
	Southwest UMETA(DisplayName = "Southwest"),
};
