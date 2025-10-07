// Copyright Leavemydogalone


#include "Grid/GridFunctionLibrary.h"
#include "Grid/Data/GridShapeInfo.h"
#include "Grid/Data/GridTypes.h"
#include "Grid/Grid.h"
#include "Game/GridV1GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GridV1/GridV1.h"
#include "GridV1GameplayTags.h"
#include "Engine/World.h"
#include "DeveloperSettings/GridV1DeveloperSettings.h"
#include "NativeGameplayTags.h"

const TArray<FHex> UGridFunctionLibrary::hex_directions = {
	   FHex(1, 0, -1), //North
       FHex(0, 1, -1), //NorthEast
       FHex(-1, 1, 0), //SouthEast
	   FHex(-1, 0, 1), //South
       FHex(0, -1, 1), //SouthWest
       FHex(1, -1, 0), //NorthWest
};

//const TArray<FHex> UGridFunctionLibrary::hex_directions = {
//       FHex(1, 0, -1), //SouthEast
//       FHex(1, -1, 0), //SouthEast
//       FHex(0, -1, 1), //South
//       FHex(-1, 0, 1), //SouthWest
//       FHex(-1, 1, 0), //NorthWest
//       FHex(0, 1, -1) //North
//};

const FOrientation UGridFunctionLibrary::layout_flat
= FOrientation(sqrt(3.0), sqrt(3.0) / 2.0, 0.0, 3.0 / 2.0,
	sqrt(3.0) / 3.0, -1.0 / 3.0, 0.0, 2.0 / 3.0,
	0.5);
//= FOrientation(3.0 / 2.0, 0.0, sqrt(3.0) / 2.0, sqrt(3.0),
//	2.0 / 3.0, 0.0, -1.0 / 3.0, sqrt(3.0) / 3.0,
//	0.0);
//= FOrientation(
//    sqrt(3.0) / 2.0, sqrt(3.0),
//    3.0 / 2.0, 0.0,
//    -1.0 / 3.0, sqrt(3.0) / 3.0,
//    0.0, 2.0 / 3.0,
//    0.0 // no offset
//);

AActor* UGridFunctionLibrary::GetGridManager(UObject* WorldContextObject)
{
	return UGameplayStatics::GetActorOfClass(WorldContextObject, AGrid::StaticClass());
}

FVector UGridFunctionLibrary::Convert2DTo3DActorHeight(const FVector2D& InVector, const FVector& ActorLocation)
{
	return FVector(InVector.X, InVector.Y, ActorLocation.Z);
}

FVector2D UGridFunctionLibrary::Convert3DTo2D(const FVector& InVector)
{
	return FVector2D(InVector.X, InVector.Y);
}



