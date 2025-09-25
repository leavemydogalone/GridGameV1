// Copyright Leavemydogalone

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "GridTypes.generated.h"

UENUM(BlueprintType)
enum class EHexMoveType : uint8
{
	None,
	Forward,
	Backward,
	ForwardLeft,
	ForwardRight,
	BackwardLeft,
	BackwardRight,
	RotateLeft,
	RotateRight
};

// Will need to convert this to left/right verbiage
UENUM(BlueprintType)
enum class EHexDirection : uint8
{
	North		UMETA(DisplayName = "North"),
	South		UMETA(DisplayName = "South"),
	NorthEast	UMETA(DisplayName = "NorthEast"),
	NorthWest	UMETA(DisplayName = "NorthWest"),
	SouthEast	UMETA(DisplayName = "SouthEast"),
	SouthWest	UMETA(DisplayName = "SouthWest"),
};



USTRUCT(BlueprintType)
struct FCubeCoord
{
	GENERATED_BODY()

public:

	// Default constructor (needed by Unreal)
	FCubeCoord() : Q(0), R(0), S(0) {}

	// Custom constructor
	FCubeCoord(int32 InQ, int32 InR, int32 InS)
		: Q(InQ), R(InR), S(InS) {
	}

	int32 Q;

	int32 R;

	int32 S;
};

USTRUCT(BlueprintType)
struct FCubeCoordF
{
	GENERATED_BODY()

public:

	float Q, R, S;

	FCubeCoordF() : Q(0.0f), R(0.0f), S(0.0f) {};

	FCubeCoordF(float InQ, float InR, float InS)
		: Q(InQ), R(InR), S(InS) {
	}
};