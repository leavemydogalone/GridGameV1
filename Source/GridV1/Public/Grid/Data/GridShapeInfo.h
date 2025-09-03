// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "GridShapeInfo.generated.h"

UENUM(BlueprintType)
enum class EGridShape : uint8
{
	Square		UMETA(DisplayName = "Square"),
	Hexagon		UMETA(DisplayName = "Hexagon")
};

USTRUCT(BlueprintType)
struct FGridInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag GridTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EGridShape GridShape = EGridShape::Square;

	// Update the size of the mesh if it is different than the default 100x100x100
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector MeshSize = FVector(100.f, 100.f, 100.f);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMesh> Mesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> Material = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UStaticMesh> FlatMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> FlatBorderMaterial = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UMaterialInstance> FlatFilledMaterial = nullptr;
};

/**
 * 
 */
UCLASS()
class GRIDV1_API UGridShapeInfo : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GridInformation")
	TArray<FGridInfo> GridInformation;

	FGridInfo FindGridInfoForTag(const EGridShape& GridShape, bool bLogNotFound = false) const;
	
};
