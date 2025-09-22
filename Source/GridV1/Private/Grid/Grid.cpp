// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/Grid.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Grid/Data/GridShapeInfo.h"
#include "DeveloperSettings/GridV1DeveloperSettings.h"
#include "Grid/GridFunctionLibrary.h"

AGrid::AGrid()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	GridHexagons = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("GridMesh"));
	
	GridHexagons->SetupAttachment(GetRootComponent());

	GridCenterCylinders = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("GridCenterCylinders"));
	GridCenterCylinders->SetupAttachment(GetRootComponent());

}

//Called when an instance of this class is placed (in editor) or spawned
void AGrid::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	//SpawnGrid();
}

void AGrid::BeginPlay()
{
	Super::BeginPlay();
	GridHexagons->SetStaticMesh(HexagonMesh);
	GridHexagons->SetMaterial(0, HexagonMaterial);
	GridHexagons->SetWorldScale3D(TileScale);

	GridCenterCylinders->SetStaticMesh(CylinderMesh);


	SpawnGrid();
}


void AGrid::SpawnGrid()
{
	GridHexagons->ClearInstances();
	GridCenterCylinders->ClearInstances();

	GridTileCount.X = FMath::RoundToInt(GridTileCount.X);
	GridTileCount.Y = FMath::RoundToInt(GridTileCount.Y);

	SpawnHexagonalGrid();

}

void AGrid::SpawnHexagonalGrid()
{
	const UGridV1DeveloperSettings* GridSettings = GetDefault<UGridV1DeveloperSettings>();

	TSet<FHex> MapContainer;

	UGridFunctionLibrary::CreateRectangularGrid(MapContainer, GridTileCount.X, GridTileCount.Y);

	UGridFunctionLibrary::Layout Layout(
		UGridFunctionLibrary::layout_flat,
		FVector2D(GridTileSize.X, GridTileSize.Y),
		FVector2D::ZeroVector
	);


	for (const FHex& Hex : MapContainer)
	{
		FVector2D WorldPos2D = UGridFunctionLibrary::hex_to_pixel(Layout, Hex);
		FVector WorldPos(WorldPos2D.X, WorldPos2D.Y, 0.f);

		// Example: spawn debug sphere
		DrawDebugSphere(GetWorld(), WorldPos, 20.f, 12, FColor::Blue, true);

		// Or: spawn an actor/ISM instance at WorldPos
		const FTransform InstanceTransform = FTransform(FRotator::ZeroRotator, WorldPos, TileScale);
		GridHexagons->AddInstanceWorldSpace(InstanceTransform);
	}



	//for (int32 i = 0; i < GridTileCount.X; i++)
	//{
	//	int32 FirstIndexOfRow = i % 2;
	//	//For the Doubled coordinates system of Hexagonal grids, we double either the row or column coordinates. Here we are 
	//	int32 DoubledRowIndex = GridTileCount.Y * 2;

	//	for (int32 j = FirstIndexOfRow; j < DoubledRowIndex; j++)
	//	{
	//		float VerticalOffset = static_cast<float>(i);
	//		float HorizontalOffset = static_cast<float>(j);

	//		VerticalOffset = i * 0.75f;
	//		HorizontalOffset = j * 0.5f;

	//		const FVector InstanceLocation = FVector(
	//			GridBottomLeftCornerLocation.X + (VerticalOffset * GridTileSize.X) + (GridTileSize.X / 2),
	//			GridBottomLeftCornerLocation.Y + (HorizontalOffset * GridTileSize.Y) + (GridTileSize.Y / 2),
	//			GridBottomLeftCornerLocation.Z
	//		);

	//		const FTransform InstanceTransform = FTransform(FRotator::ZeroRotator, InstanceLocation, TileScale);
	//		GridMesh->AddInstanceWorldSpace(InstanceTransform);

	//		FVector CylinderScale = FVector(CenterRadius / 50.f, CenterRadius / 50.f, CenterHeight / 100.f);
	//		FVector CylinderLocation = InstanceLocation;
	//		CylinderLocation.Z += CenterHeight / 2.f; 
	//		FTransform CylinderTransform(FRotator::ZeroRotator, CylinderLocation, CylinderScale);

	//		GridCenterCylinders->AddInstanceWorldSpace(CylinderTransform);

	//		j++;

	//	}
	//}
}

