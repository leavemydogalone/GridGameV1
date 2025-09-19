// Copyright Leavemydogalone

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Grid/Data/GridShapeInfo.h"
#include "Grid/Data/GridTypes.h"
#include "GridFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class GRIDV1_API UGridFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Grid")
	static UGridShapeInfo* GetGridInfo(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	static FVector SnapVectorToVector(FVector V1, FVector V2);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	static FVector SnapVectorToGrid(FVector InVector);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	static FVector SnapVectorToHexCenter(FVector WorldPos);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	static bool IsFloatEven(float InFloat);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	static FVector TraceForGround(FVector StartLocation, bool HitSomething, FVector GridTileSize, UObject* WorldContextObject);


	UFUNCTION(BlueprintCallable, Category = "Grid")
	static bool IsAtHexCenter(const AActor* Actor);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	static FVector GetNextHexCenterInDirection(FVector StartLocation, const EHexDirection Direction);

	/* Hexagonal Grid Math Helpers */
	UFUNCTION(BlueprintCallable, Category = "Grid")
	static FCubeCoordF WorldToHex(FVector World, FVector2D HexSize);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	static FCubeCoord CubeRound(FCubeCoordF HexF);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	static FVector HexToWorld(FCubeCoord Cube, FVector2D HexSize, float Z = 0.f);

	//Function to convert direction based on controller rotation
	UFUNCTION(BlueprintCallable, Category = "Grid")
	static FVector2D GetHexUnitVector(EHexDirection Dir);

	//UFUNCTION(BlueprintCallable, Category = "Grid")
	//static FVector2D GetDirectionFromGameplayTag(FGameplayTag& GameplayTag);
};
