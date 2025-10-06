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

	/* Grid Interface */
	UFUNCTION()
	virtual FVector2D GetHexCenterAtLocation(FVector Location) override;
	UFUNCTION()
	virtual FHex GetHexAtLocation(FVector2D Location) override;
	UFUNCTION()
	virtual FVector2D GetNextHexCenter(FVector StartLocation, int32 Direction) override;
	UFUNCTION()
	virtual void HandlePlayerMoveIntoHex(FVector Location, int32 TeamId) override;
	UFUNCTION()
	virtual bool CanPlayerMoveIntoHex(FVector Location, int32 TeamId) override;
	UFUNCTION()
	virtual bool IsHexOccupiedOrReserved(FVector2D Location) override;
	UFUNCTION()
	virtual bool TryEnterHex(FHex CurrentHex, FHex Hex) override;

	/* End Grid Interface */


	UPROPERTY(EditAnywhere, Category = "Grid")
	bool DebugVisuals = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	/* Hex Grid */
	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	TObjectPtr<UInstancedStaticMeshComponent> GridHexagons;

	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	TObjectPtr<UStaticMesh> HexagonMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	TObjectPtr<UMaterialInterface> HexagonMaterial;

	UPROPERTY(EditAnywhere, Category = "Grid")
	FVector GridTileSize = FVector(100.f, 100.f, 100.f);

	UPROPERTY(EditAnywhere, Category = "Grid")
	FVector2D GridTileCount = FVector2D(10, 10);
	
	/* Cylinder */
	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	TObjectPtr<UStaticMesh> CylinderMesh;

	UPROPERTY()
	TObjectPtr<UInstancedStaticMeshComponent> GridCenterCylinders;


	UFUNCTION()
	void SpawnGrid();

	void SetUpGrid();

	void SetGridMeshInfo();

	void SpawnHexagonalGrid();

	FLayout GridLayout;
	TSet<FHex> MapContainer;

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_UpdateHexTeam(int32 Index, int32 TeamId);

};
