// Copyright Leavemydogalone

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Grid/Data/GridShapeInfo.h"
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

};
