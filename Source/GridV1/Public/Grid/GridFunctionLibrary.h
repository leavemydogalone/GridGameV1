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
	static FVector GetNextHexCenterInDirection(FVector StartLocation, const EHexDirection Direction);
};
