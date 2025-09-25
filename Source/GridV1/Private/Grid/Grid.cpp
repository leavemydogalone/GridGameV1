// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/Grid.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Grid/Data/GridShapeInfo.h"
#include "DeveloperSettings/GridV1DeveloperSettings.h"
#include "Components/TextRenderComponent.h"
#include "Grid/GridFunctionLibrary.h"

DEFINE_LOG_CATEGORY(LogGrid);

AGrid::AGrid() 
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	GridHexagons = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("GridMesh"));
	
	GridHexagons->SetupAttachment(GetRootComponent());

	GridCenterCylinders = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("GridCenterCylinders"));
	GridCenterCylinders->SetupAttachment(GetRootComponent());

	// Fix: Construct GridLayout as a local variable and assign its value to the member variable

}


//Called when an instance of this class is placed (in editor) or spawned
void AGrid::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	GridHexagons->SetStaticMesh(HexagonMesh);
	GridHexagons->SetMaterial(0, HexagonMaterial);

	GridCenterCylinders->SetStaticMesh(CylinderMesh);
	SpawnGrid();
}

void AGrid::GetCurrentHexAtLocation_Implementation(FVector Location)
{
	FHex Hex = UGridFunctionLibrary::pixel_to_hex_rounded(GridLayout, FVector2D(Location.X, Location.Y));
	FString CoordText = FString::Printf(TEXT("Q:%d R:%d S:%d"), Hex.q, Hex.r, Hex.s);

	//Add log of coortext
	UE_LOG(LogGrid, Log, TEXT("Current Hex Position: %s"), *CoordText);
}

//FVector AGrid::GetLocationOfNextHexInDirection_Implementation(FVector StartLocation, FHex Hex)
//{
//	return FVector();
//}

void AGrid::BeginPlay()
{
	Super::BeginPlay();
	GridHexagons->SetStaticMesh(HexagonMesh);
	GridHexagons->SetMaterial(0, HexagonMaterial);

	GridCenterCylinders->SetStaticMesh(CylinderMesh);


	SpawnGrid();
}


void AGrid::SpawnGrid()
{
	MapContainer.Empty();
	GridHexagons->ClearInstances();
	GridCenterCylinders->ClearInstances();

	GridTileCount.X = FMath::RoundToInt(GridTileCount.X);
	GridTileCount.Y = FMath::RoundToInt(GridTileCount.Y);

	SpawnHexagonalGrid();

}

void AGrid::SetUpGrid()
{
}

void AGrid::SpawnHexagonalGrid()
{
	const UGridV1DeveloperSettings* GridSettings = GetDefault<UGridV1DeveloperSettings>();

	UGridFunctionLibrary::CreateRectangularGrid(MapContainer, GridTileCount.X, GridTileCount.Y);

	GridLayout = FLayout(
		UGridFunctionLibrary::layout_flat,
		FVector2D(GridTileSize.X, GridTileSize.Y),
		FVector2D::ZeroVector
	);

	for (const FHex& Hex : MapContainer)
	{
		FVector2D WorldPos2D = UGridFunctionLibrary::hex_to_pixel(GridLayout, Hex);
		FVector WorldPos(WorldPos2D.X, WorldPos2D.Y, 0.f);

		if (DebugVisuals)
		{
			FString CoordText = FString::Printf(TEXT("Q:%d R:%d S:%d"), Hex.q, Hex.r, Hex.s);

			DrawDebugString(GetWorld(), WorldPos + FVector(0, 0, 250.f), CoordText, nullptr, FColor::Blue, 1000.f, true);

		}

		// Or: spawn an actor/ISM instance at WorldPos
		const FTransform InstanceTransform = FTransform(FRotator::ZeroRotator, WorldPos, TileScale);
		GridHexagons->AddInstanceWorldSpace(InstanceTransform);
	}
}

