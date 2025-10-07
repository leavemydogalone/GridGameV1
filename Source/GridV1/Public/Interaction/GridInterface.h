// Copyright Leavemydogalone

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Grid/GridFunctionLibrary.h"
#include "GridInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, BlueprintType)
class UGridInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GRIDV1_API IGridInterface
{
	GENERATED_BODY()

	
public:

	UFUNCTION()
	virtual FLayout GetLayout() = 0;

	UFUNCTION()
	virtual FVector2D GetHexCenterAtLocation(FVector Location) = 0;

	UFUNCTION()
	virtual FHex GetHexAtLocation(FVector2D Location) = 0;

	UFUNCTION()
	virtual FVector2D GetNextHexCenter(FVector StartLocation, int32 Direction) = 0;

	UFUNCTION()
	virtual void HandlePlayerMoveIntoHex(FVector Location, int32 TeamId) = 0;

	UFUNCTION()
	virtual bool CanPlayerMoveIntoHex(FVector Location, int32 TeamId) = 0;

	UFUNCTION()
	virtual bool IsHexOccupiedOrReserved(FVector2D Location) = 0;

	UFUNCTION()
	virtual bool TryEnterHex(FHex CurrentHex, FHex Hex) = 0;

};
