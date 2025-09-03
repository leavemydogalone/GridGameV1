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


	UPROPERTY(EditAnywhere, Category = "Grid")
	FVector GridCenter;

	//UPROPERTY()
	FVector GridBottomLeftCornerLocation;

	UPROPERTY(EditAnywhere, Category = "Grid")
	FVector GridTileSize;

	UPROPERTY(EditAnywhere, Category = "Grid")
	FVector2D GridTileCount;

	UPROPERTY(EditAnywhere, Category = "Grid")
	EGridShape GridShape;

	UFUNCTION()
	void SpawnGrid();

	void SetGridInfo();
};
