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

UENUM(BlueprintType)
enum class EOccupancyStates : uint8
{
	Free		UMETA(DisplayName = "Free"),
	Occupied	UMETA(DisplayName = "Occupied"),
	Reserved	UMETA(DisplayName = "Reserved"),
};

USTRUCT(BlueprintType)
struct FHex
{
	GENERATED_BODY();

	int32 q;
	int32 r;
	int32 s;

	bool Occupied = false;
	EOccupancyStates OccupancyState = EOccupancyStates::Free;

	int32 TeamId = 0;
	int32 Index = -1;

	FHex(int32 Inq, int32 Inr, int32 Ins)
		: q(Inq), r(Inr), s(Ins)
	{
		check(q + r + s == 0);
	}

	FHex()
		: q(0), r(0), s(0)
	{
	}

	FORCEINLINE bool operator == (const FHex& Other) const
	{
		return q == Other.q && r == Other.r && s == Other.s;
	}

	FORCEINLINE bool operator != (const FHex& Other) const
	{
		return !(*this == Other);
	}

};

static const TMap<EHexDirection, FHex> DirectionToHex = {
	{EHexDirection::North,     FHex(0, -1, 1)},
	{EHexDirection::South,     FHex(0, 1, -1)},
	{EHexDirection::NorthEast, FHex(1, -1, 0)},
	{EHexDirection::NorthWest, FHex(-1, 0, 1)},
	{EHexDirection::SouthEast, FHex(1, 0, -1)},
	{EHexDirection::SouthWest, FHex(-1, 1, 0)}
};

static const TMap<EHexDirection, FRotator> DirectionToRotation = {
	{EHexDirection::North,     FRotator(0.f,   0.f, 0.f)},
	{EHexDirection::NorthEast, FRotator(0.f,  60.f, 0.f)},
	{EHexDirection::SouthEast, FRotator(0.f, 120.f, 0.f)},
	{EHexDirection::South,     FRotator(0.f, 180.f, 0.f)},
	{EHexDirection::SouthWest, FRotator(0.f, 240.f, 0.f)},
	{EHexDirection::NorthWest, FRotator(0.f, 300.f, 0.f)}
};

//rotation to hex direction



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