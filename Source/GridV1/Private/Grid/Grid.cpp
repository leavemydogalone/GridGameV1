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

// A second function should be created for hexagon and square

void AGrid::SpawnGrid()
{
	GridMesh->ClearInstances();

	//Round the tile count to nearest whole number
	GridTileCount.X = FMath::RoundToInt(GridTileCount.X);
	GridTileCount.Y = FMath::RoundToInt(GridTileCount.Y);

	if (GridShape == EGridShape::Hexagon) {
		SpawnHexagonalGrid();
	}
	else if (GridShape == EGridShape::Square) {
		SpawnSquareGrid();
	}


	////Hexagon
	//int32 NumRows = GridTileCount.Y;
	//if (GridShape == EGridShape::Hexagon)
	//{
	//	NumRows = GridTileCount.Y * 2;
	//}

	//for (int32 i = 0; i < GridTileCount.X; i++)
	//{
	//	for (int32 j = 0; j < NumRows; j++)
	//	{
	//		float XOffset = static_cast<float>(i);
	//		float YOffset = static_cast<float>(j);

	//		if (GridShape == EGridShape::Hexagon)
	//		{
	//			XOffset = i * 0.75f;
	//			YOffset = j + (i % 2) * 0.5f;

	//		}
	//		const FVector InstanceLocation = FVector(
	//			GridBottomLeftCornerLocation.X + (XOffset * GridTileSize.X) + (GridTileSize.X / 2),
	//			GridBottomLeftCornerLocation.Y + (YOffset * GridTileSize.Y) + (GridTileSize.Y / 2),
	//			GridBottomLeftCornerLocation.Z
	//		);
	//		const FTransform InstanceTransform = FTransform(FRotator::ZeroRotator, InstanceLocation, FVector(1.f, 1.f, 1.f));

	//		GridMesh->AddInstanceWorldSpace(InstanceTransform);

	//		if (GridShape == EGridShape::Hexagon){
	//			j++;
	//		}

	//	}
	//}

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

	GridMesh->SetStaticMesh(FoundGridInfo.FlatMesh);
	GridMesh->SetMaterial(0, FoundGridInfo.FlatBorderMaterial);

	// This is to allow meshes that are of different sizes in the grid info. Will also need to set MeshSize in gridinfo
	GridMesh->SetWorldScale3D(GridTileSize / FoundGridInfo.MeshSize);

}

void AGrid::SetGridCenterAndBottomLeft()
{
	FVector CenterSnappedToGrid;

	switch (GridShape)
	{

	case EGridShape::Square:

		FVector2D EvenTileCount = GridTileCount;
		if (UGridFunctionLibrary::IsFloatEven(GridTileCount.X) == false)
		{
			EvenTileCount.X -= 1;
		}
		if (UGridFunctionLibrary::IsFloatEven(GridTileCount.Y) == false)
		{
			EvenTileCount.Y -= 1;
		}

		CenterSnappedToGrid = UGridFunctionLibrary::SnapVectorToVector(GridCenter, GridTileSize);

		CenterSnappedToGrid.Z = GetActorLocation().Z;

		GridBottomLeftCornerLocation = CenterSnappedToGrid - FVector(GridTileSize.X * (EvenTileCount.X / 2), GridTileSize.Y * (EvenTileCount.Y / 2), 0.f);

		break;


	case EGridShape::Hexagon:
		
		FVector UpdatedTileSize = GridTileSize * FVector(1.5f, 1.f, 1.f);
		CenterSnappedToGrid = UGridFunctionLibrary::SnapVectorToVector(GridCenter, UpdatedTileSize);

		CenterSnappedToGrid.Z = GetActorLocation().Z;

		FVector BottomLeftCornerDistanceFromCenter = FVector(UpdatedTileSize.X * (GridTileCount.X / 3), UpdatedTileSize.Y * (GridTileCount.Y / 2), 0.f);

		GridBottomLeftCornerLocation = CenterSnappedToGrid - UGridFunctionLibrary::SnapVectorToVector(BottomLeftCornerDistanceFromCenter, UpdatedTileSize);

		break;

	default:
		break;
	}

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
			float XOffset = static_cast<float>(i);
			float YOffset = static_cast<float>(j);

			XOffset = i * 0.75f;
			YOffset = j * 0.5f;

			const FVector InstanceLocation = FVector(
				GridBottomLeftCornerLocation.X + (XOffset * GridTileSize.X) + (GridTileSize.X / 2),
				GridBottomLeftCornerLocation.Y + (YOffset * GridTileSize.Y) + (GridTileSize.Y / 2),
				GridBottomLeftCornerLocation.Z
			);

			const FTransform InstanceTransform = FTransform(FRotator::ZeroRotator, InstanceLocation, FVector(1.f, 1.f, 1.f));

			GridMesh->AddInstanceWorldSpace(InstanceTransform);

			j++;

		}
	}
}

void AGrid::SpawnSquareGrid()
{
	for (int32 i = 0; i < GridTileCount.X; i++)
	{
		for (int32 j = 0; j < GridTileCount.Y; j++)
		{
			const FVector InstanceLocation = FVector(
				GridBottomLeftCornerLocation.X + (i * GridTileSize.X) + (GridTileSize.X / 2),
				GridBottomLeftCornerLocation.Y + (j * GridTileSize.Y) + (GridTileSize.Y / 2),
				GridBottomLeftCornerLocation.Z
			);

			const FTransform InstanceTransform = FTransform(FRotator::ZeroRotator, InstanceLocation, FVector(1.f, 1.f, 1.f));

			GridMesh->AddInstanceWorldSpace(InstanceTransform);

		}
	}
}



