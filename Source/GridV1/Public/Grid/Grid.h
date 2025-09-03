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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TObjectPtr<UInstancedStaticMeshComponent> GridMesh;

	UPROPERTY()
	TObjectPtr<UMaterialInterface> GridMaterial;

	UFUNCTION()
	void SpawnGrid();

	UPROPERTY()
	FVector GridCenter;

	UPROPERTY()
	FVector GridBottomLeftCornerLocation;

	UPROPERTY()
	FVector GridTileSize;

	UPROPERTY()
	FVector2D GridTileCount;

	UPROPERTY()
	EGridShape GridShape;

	void SetGridInfo();

	void SetGridBottomLeftCornerLocation();
};
