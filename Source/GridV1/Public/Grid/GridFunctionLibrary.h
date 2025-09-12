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
	static bool IsFloatEven(float InFloat);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	static FVector TraceForGround(FVector StartLocation, bool HitSomething, FVector GridTileSize, UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	static FVector2D GetHexUnitVector(EHexDirection Dir);

	UFUNCTION(BlueprintCallable, Category = "Grid")
	static bool IsAtHexCenter(const AActor* Actor);

	//UFUNCTION(BlueprintCallable, Category = "Grid")
	//static FVector2D GetDirectionFromGameplayTag(FGameplayTag& GameplayTag);
};
