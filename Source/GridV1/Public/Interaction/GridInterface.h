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

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Grid")
	void GetCurrentHexAtLocation(FVector Location);
};
