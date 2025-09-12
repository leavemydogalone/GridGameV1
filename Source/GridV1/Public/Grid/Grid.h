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

	//This is so we can see the updated tile size in the editor preview. Will be overriden in play
	UPROPERTY(EditAnywhere, Category = "Grid")
	FVector TileScale = FVector(1.f, 1.f, 1.f);

	UPROPERTY(EditAnywhere, Category = "Grid")
	FVector GridTileSize = FVector(100.f, 100.f, 100.f);

	UPROPERTY(EditAnywhere, Category = "Grid")
	FVector2D GridTileCount = FVector2D(10, 10);

	UPROPERTY(EditAnywhere, Category = "Grid")
	EGridShape GridShape = EGridShape::Square;

	UPROPERTY(EditAnywhere, Category = "Grid")
	bool UseEnvironment = false;

	UFUNCTION()
	void SpawnGrid();

	void SetUpGrid();

	void SetGridMeshInfo();

	void SetGridCenterAndBottomLeft();

	void SpawnHexagonalGrid();

	void SpawnSquareGrid();
	

};
