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
	   FHex(1, 0, -1), FHex(1, -1, 0), FHex(0, -1, 1),
	   FHex(-1, 0, 1), FHex(-1, 1, 0), FHex(0, 1, -1)
};

const FOrientation UGridFunctionLibrary::layout_flat
//= FOrientation(sqrt(3.0), sqrt(3.0) / 2.0, 0.0, 3.0 / 2.0,
//	sqrt(3.0) / 3.0, -1.0 / 3.0, 0.0, 2.0 / 3.0,
//	0.5);
//= FOrientation(3.0 / 2.0, 0.0, sqrt(3.0) / 2.0, sqrt(3.0),
//	2.0 / 3.0, 0.0, -1.0 / 3.0, sqrt(3.0) / 3.0,
//	0.0);
= FOrientation(
    sqrt(3.0) / 2.0, sqrt(3.0),
    3.0 / 2.0, 0.0,
    -1.0 / 3.0, sqrt(3.0) / 3.0,
    0.0, 2.0 / 3.0,
    0.0 // no offset
);

AActor* UGridFunctionLibrary::GetGridManager(UObject* WorldContextObject)
{
	return UGameplayStatics::GetActorOfClass(WorldContextObject, AGrid::StaticClass());
}

