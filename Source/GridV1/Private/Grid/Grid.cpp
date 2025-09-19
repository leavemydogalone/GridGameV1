// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/Grid.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Grid/Data/GridShapeInfo.h"
#include "Grid/GridFunctionLibrary.h"

AGrid::AGrid()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	GridMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("GridMesh"));
	GridMesh->SetupAttachment(GetRootComponent());

	GridCenterCylinders = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("GridCenterCylinders"));
	GridCenterCylinders->SetupAttachment(GetRootComponent());
}

//Called when an instance of this class is placed (in editor) or spawned
void AGrid::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	SetUpGrid();
	SpawnGrid();
}

void AGrid::BeginPlay()
{
	Super::BeginPlay();

	SetUpGrid();
	SpawnGrid();
}


void AGrid::SetUpGrid()
{
	GridCenter = GetActorLocation();
	SetGridMeshInfo();
	SetGridCenterAndBottomLeft();
}

void AGrid::SetGridMeshInfo()
{
	const UGridShapeInfo* GridInfo = UGridFunctionLibrary::GetGridInfo(this);
	if (GridInfo == nullptr) return;

	const FGridInfo FoundGridInfo = GridInfo->FindGridInfoForTag(GridShape);
	if (FoundGridInfo.Mesh == nullptr || FoundGridInfo.Material == nullptr) return;

	TileScale = GridTileSize / FoundGridInfo.MeshSize;

	GridMesh->SetStaticMesh(FoundGridInfo.FlatMesh);
	GridMesh->SetMaterial(0, FoundGridInfo.FlatBorderMaterial);
	GridMesh->SetWorldScale3D(GridTileSize / FoundGridInfo.MeshSize);

	GridCenterCylinders->SetStaticMesh(CylinderMesh);

}

void AGrid::SetGridCenterAndBottomLeft()
{
	FVector CenterSnappedToGrid;

	switch (GridShape)
	{

	case EGridShape::Hexagon:
		
		//V2

		CenterSnappedToGrid = UGridFunctionLibrary::SnapVectorToHexCenter(GridCenter);

		CenterSnappedToGrid.Z = GetActorLocation().Z;

		/*FVector BottomLeftCornerDistanceFromCenter = FVector(GridTileSize.X * (GridTileCount.X / 3), UpdatedTileSize.Y * (GridTileCount.Y / 2), 0.f);*/

		GridBottomLeftCornerLocation = CenterSnappedToGrid;


		/// V1
		//FVector UpdatedTileSize = GridTileSize * FVector(1.5f, 1.f, 1.f);
		//CenterSnappedToGrid = UGridFunctionLibrary::SnapVectorToVector(GridCenter, UpdatedTileSize);

		//CenterSnappedToGrid.Z = GetActorLocation().Z;

		//FVector BottomLeftCornerDistanceFromCenter = FVector(UpdatedTileSize.X * (GridTileCount.X / 3), UpdatedTileSize.Y * (GridTileCount.Y / 2), 0.f);

		//GridBottomLeftCornerLocation = CenterSnappedToGrid - UGridFunctionLibrary::SnapVectorToVector(BottomLeftCornerDistanceFromCenter, UpdatedTileSize);

		break;

	default:
		break;
	}

}

void AGrid::SpawnGrid()
{
	GridMesh->ClearInstances();
	GridCenterCylinders->ClearInstances();

	GridTileCount.X = FMath::RoundToInt(GridTileCount.X);
	GridTileCount.Y = FMath::RoundToInt(GridTileCount.Y);

	SpawnHexagonalGrid();

}

void AGrid::SpawnHexagonalGrid()
{
	for (int32 i = 0; i < GridTileCount.X; i++)
	{
		int32 FirstIndexOfRow = i % 2;
		//For the Doubled coordinates system of Hexagonal grids, we double either the row or column coordinates. Here we are 
		int32 DoubledRowIndex = GridTileCount.Y * 2;

		for (int32 j = FirstIndexOfRow; j < DoubledRowIndex; j++)
		{
			float VerticalOffset = static_cast<float>(i);
			float HorizontalOffset = static_cast<float>(j);

			VerticalOffset = i * 0.75f;
			HorizontalOffset = j * 0.5f;

			const FVector InstanceLocation = FVector(
				GridBottomLeftCornerLocation.X + (VerticalOffset * GridTileSize.X) + (GridTileSize.X / 2),
				GridBottomLeftCornerLocation.Y + (HorizontalOffset * GridTileSize.Y) + (GridTileSize.Y / 2),
				GridBottomLeftCornerLocation.Z
			);

			const FTransform InstanceTransform = FTransform(FRotator::ZeroRotator, InstanceLocation, TileScale);
			GridMesh->AddInstanceWorldSpace(InstanceTransform);

			FVector CylinderScale = FVector(CenterRadius / 50.f, CenterRadius / 50.f, CenterHeight / 100.f);
			FVector CylinderLocation = InstanceLocation;
			CylinderLocation.Z += CenterHeight / 2.f; 
			FTransform CylinderTransform(FRotator::ZeroRotator, CylinderLocation, CylinderScale);

			GridCenterCylinders->AddInstanceWorldSpace(CylinderTransform);

			j++;

		}
	}
}

