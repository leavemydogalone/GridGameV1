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

	GridCenter = GetActorLocation();

}

//Called when an instance of this class is placed (in editor) or spawned
void AGrid::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	GridCenter = GetActorLocation();
	SetGridInfo();
	SpawnGrid();
}

void AGrid::BeginPlay()
{
	Super::BeginPlay();

	GridCenter = GetActorLocation();
	SetGridInfo();
	SpawnGrid();
}

void AGrid::SpawnGrid()
{
	GridMesh->ClearInstances();
	FVector CenterSnappedToGrid = UGridFunctionLibrary::SnapVectorToVector(GridCenter, GridTileSize);

	CenterSnappedToGrid.Z = GetActorLocation().Z;


	GridBottomLeftCornerLocation = CenterSnappedToGrid - FVector(GridTileSize.X * (GridTileCount.X / 2), GridTileSize.Y * (GridTileCount.Y / 2), 0.f);


	for (int32 i = 0; i < GridTileCount.X; i++)
	{
		for (int32 j = 0; j < GridTileCount.Y; j++)
		{
			const FVector InstanceLocation = FVector(GridBottomLeftCornerLocation.X + (i * GridTileSize.X) + (GridTileSize.X / 2), GridBottomLeftCornerLocation.Y + (j * GridTileSize.Y) + (GridTileSize.Y / 2), GridBottomLeftCornerLocation.Z);
			const FTransform InstanceTransform = FTransform(FRotator::ZeroRotator, InstanceLocation, FVector(1.f, 1.f, 1.f));

			GridMesh->AddInstanceWorldSpace(InstanceTransform);
		}
	}

}

void AGrid::SetGridInfo()
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



