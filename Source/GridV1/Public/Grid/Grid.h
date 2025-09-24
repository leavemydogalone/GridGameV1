// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid/Data/GridShapeInfo.h"
#include "Grid/GridFunctionLibrary.h"
#include "Interaction/GridInterface.h"
#include "Grid.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogGrid, Log, All);

UCLASS()
class GRIDV1_API AGrid : public AActor , public IGridInterface 
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrid();
	
	virtual void OnConstruction(const FTransform& Transform) override;

	UFUNCTION(BlueprintCallable, Category = "Grid")
	void GetCurrentHexAtLocation_Implementation(FVector Location) override;

	UPROPERTY(EditAnywhere, Category = "Grid")
	bool DebugVisuals = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	/* Hex Grid */
	UPROPERTY()
	TObjectPtr<UInstancedStaticMeshComponent> GridHexagons;

	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	TObjectPtr<UStaticMesh> HexagonMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	TObjectPtr<UMaterialInterface> HexagonMaterial;

	//This is so we can see the updated tile size in the editor preview. Will be overriden in play
	UPROPERTY(EditAnywhere, Category = "Grid")
	FVector TileScale = FVector(1.f, 1.f, 1.f);

	UPROPERTY(EditAnywhere, Category = "Grid")
	FVector GridTileSize = FVector(100.f, 100.f, 100.f);

	UPROPERTY(EditAnywhere, Category = "Grid")
	FVector2D GridTileCount = FVector2D(10, 10);
	
	/* Cylinder */
	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	TObjectPtr<UStaticMesh> CylinderMesh;

	UPROPERTY()
	TObjectPtr<UInstancedStaticMeshComponent> GridCenterCylinders;

	// Adjustable radius for overlap cylinders
	UPROPERTY(EditAnywhere, Category = "Grid")
	float CenterRadius = 50.f;

	UPROPERTY(EditAnywhere, Category = "Grid")
	float CenterHeight = 100.f;

	UFUNCTION()
	void SpawnGrid();

	void SetUpGrid();

	void SetGridMeshInfo();

	void SpawnHexagonalGrid();

	TSet<FHex> MapContainer;
	FLayout GridLayout;
};
