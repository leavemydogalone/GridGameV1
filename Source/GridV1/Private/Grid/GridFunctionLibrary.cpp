// Copyright Leavemydogalone


#include "Grid/GridFunctionLibrary.h"
#include "Grid/Data/GridShapeInfo.h"
#include "Grid/Data/GridTypes.h"
#include "Game/GridV1GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GridV1/GridV1.h"
#include "GridV1GameplayTags.h"
#include "Engine/World.h"
#include "DeveloperSettings/GridV1DeveloperSettings.h"
#include "NativeGameplayTags.h"

const TArray<FHex> UGridFunctionLibrary::hex_directions = {
	   FHex(1, 0, -1), FHex(1, -1, 0), FHex(0, -1, 1),
	   FHex(-1, 0, 1), FHex(-1, 1, 0), FHex(0, 1, -1)
};

FVector UGridFunctionLibrary::SnapVectorToVector(FVector V1, FVector V2)
{
	float SnappedX = UKismetMathLibrary::GridSnap_Float(V1.X, V2.X);
	float SnappedY = UKismetMathLibrary::GridSnap_Float(V1.Y, V2.Y);
	float SnappedZ = UKismetMathLibrary::GridSnap_Float(V1.Z, V2.Z);

	return FVector(SnappedX, SnappedY, SnappedZ);
}


FVector UGridFunctionLibrary::GetNextHexCenterInDirection(FVector StartLocation, const EHexDirection Direction)
{
	const UGridV1DeveloperSettings* GridSettings = GetDefault<UGridV1DeveloperSettings>();
	FVector GridTileSize = GridSettings->GridTileSize;

	float VerticalOffset =  0.75f;
	float HorizontalOffset =  0.5f;

	FVector InstanceLocation = FVector::ZeroVector;
	float DiagonalVerticalDistance = VerticalOffset * GridTileSize.X;
	float DiagonalHorizontalDistance = HorizontalOffset * GridTileSize.Y;


	switch (Direction)
	{
	case EHexDirection::Right:   
		InstanceLocation = FVector(
			StartLocation.X,
			StartLocation.Y + GridTileSize.Y,
			StartLocation.Z
		);
		break;

	case EHexDirection::Left:		
		InstanceLocation = FVector(
			StartLocation.X,
			StartLocation.Y - GridTileSize.Y,
			StartLocation.Z
		);
		break;

	case EHexDirection::UpRight:	
		InstanceLocation = FVector(
			StartLocation.X + DiagonalVerticalDistance,
			StartLocation.Y + DiagonalHorizontalDistance,
			StartLocation.Z
		);

		break;

	case EHexDirection::UpLeft:
		InstanceLocation = FVector(
			StartLocation.X + DiagonalVerticalDistance,
			StartLocation.Y - DiagonalHorizontalDistance,
			StartLocation.Z
		);

		break;

	case EHexDirection::DownRight:
		InstanceLocation = FVector(
			StartLocation.X - DiagonalVerticalDistance,
			StartLocation.Y + DiagonalHorizontalDistance,
			StartLocation.Z
		);
		break;

	case EHexDirection::DownLeft:
		InstanceLocation = FVector(
			StartLocation.X - DiagonalVerticalDistance,
			StartLocation.Y - DiagonalHorizontalDistance,
			StartLocation.Z
		);
		break;

	default:						
		break;
	}

	return InstanceLocation;

}