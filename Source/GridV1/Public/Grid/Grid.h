// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid/Data/GridShapeInfo.h"
#include "Grid.generated.h"

UCLASS()
class GRIDV1_API AGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrid();
	
	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	TObjectPtr<UInstancedStaticMeshComponent> GridMesh;

	UPROPERTY()
	TObjectPtr<UMaterialInterface> GridMaterial;


	//UPROPERTY(EditAnywhere, Category = "Grid")
	FVector GridCenter = FVector::ZeroVector;

	FVector GridBottomLeftCornerLocation;

	UPROPERTY(EditAnywhere, Category = "Grid")
	FVector GridTileSize = FVector(100.f, 100.f, 0.f);

	UPROPERTY(EditAnywhere, Category = "Grid")
	FVector2D GridTileCount = FVector2D(10, 10);

	UPROPERTY(EditAnywhere, Category = "Grid")
	EGridShape GridShape = EGridShape::Square;

	UFUNCTION()
	void SpawnGrid();

	void SetUpGrid();

	void SetGridMeshInfo();

	void SetGridCenterAndBottomLeft();

	void SpawnHexagonalGrid();

	void SpawnSquareGrid();
	//float 
};
