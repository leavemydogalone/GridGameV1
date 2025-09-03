// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/Grid.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Grid/Data/GridShapeInfo.h"
#include "Grid/GridFunctionLibrary.h"

// Sets default values
AGrid::AGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	GridMesh = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("GridMesh"));
	GridMesh->SetupAttachment(GetRootComponent());

	GridCenter = FVector::ZeroVector;
}

// Called when the game starts or when spawned
void AGrid::BeginPlay()
{
	Super::BeginPlay();
	SetGridInfo();
	SpawnGrid();
}

void AGrid::SpawnGrid()
{
	GridMesh->ClearInstances();
	for (int32 i = 0; i < GridTileCount.X; i++)
	{
		for (int32 j = 0; j < GridTileCount.Y; j++)
		{
			const FVector InstanceLocation = FVector(GridBottomLeftCornerLocation.X + (i * GridTileSize.X) + (GridTileSize.X / 2), GridBottomLeftCornerLocation.Y + (j * GridTileSize.Y) + (GridTileSize.Y / 2), GridBottomLeftCornerLocation.Z);
			const FTransform InstanceTransform = FTransform(FRotator::ZeroRotator, InstanceLocation, FVector(1.f, 1.f, 1.f));
			GridMesh->AddInstance(InstanceTransform);
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
	GridTileSize = FoundGridInfo.MeshSize;

	GridBottomLeftCornerLocation = GridCenter - FVector(GridTileSize.X * (GridTileCount.X / 2), GridTileSize.Y * (GridTileCount.Y / 2), 0.f);

}



