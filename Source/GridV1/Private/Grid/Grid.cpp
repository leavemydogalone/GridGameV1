// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/Grid.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Grid/Data/GridShapeInfo.h"
#include "DeveloperSettings/GridV1DeveloperSettings.h"
#include "Components/TextRenderComponent.h"
#include "Grid/GridFunctionLibrary.h"
#include "Grid/Data/GridTypes.h"
#include "Net/UnrealNetwork.h"


DEFINE_LOG_CATEGORY(LogGrid);

AGrid::AGrid() 
{
#if WITH_EDITOR || UE_BUILD_DEVELOPMENT
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
#else
	PrimaryActorTick.bCanEverTick = false;
#endif

	bReplicates = true;
	GridHexagons = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("GridMesh"));
	
	GridHexagons->SetupAttachment(GetRootComponent());

	GridCenterCylinders = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("GridCenterCylinders"));
	GridCenterCylinders->SetupAttachment(GetRootComponent());
}

void AGrid::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	SetUpGrid();
	SpawnGrid();
}

void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DebugVisuals)
	{
		for (FHex& Hex : MapContainer)
		{
			FString CoordText = FString::Printf(TEXT("Q:%d R:%d S:%d"), Hex.q, Hex.r, Hex.s);
			FString OccupancyText = FString::Printf(TEXT("Occupancy:%d"), Hex.OccupancyState);

			FVector WorldPos = FVector(UGridFunctionLibrary::hex_to_pixel(GridLayout, Hex).X, UGridFunctionLibrary::hex_to_pixel(GridLayout, Hex).Y, 0.f);

			DrawDebugString(GetWorld(), WorldPos + FVector(0, 0, 250.f), CoordText, nullptr, FColor::Blue, 0.f, true);
			DrawDebugString(GetWorld(), WorldPos + FVector(0, 0, 150.f), OccupancyText, nullptr, FColor::Blue, 0.f, true);

		}
		

	}
}

void AGrid::BeginPlay()
{
	Super::BeginPlay();

	SetUpGrid();
	SpawnGrid();
}

FLayout AGrid::GetLayout()
{
	return GridLayout;
}

FVector2D AGrid::GetHexCenterAtLocation(FVector Location)
{
	FHex Hex = UGridFunctionLibrary::pixel_to_hex_rounded(GridLayout, FVector2D(Location.X, Location.Y));
	FVector2D HexLocation = UGridFunctionLibrary::hex_to_pixel(GridLayout, Hex);

	return HexLocation;

}

FHex AGrid::GetHexAtLocation(FVector2D Location)
{
	return UGridFunctionLibrary::pixel_to_hex_rounded(GridLayout, Location);
}

FVector2D AGrid::GetNextHexCenter(FVector StartLocation, int32 Direction)
{
	FHex CurrentHex = UGridFunctionLibrary::pixel_to_hex_rounded(GridLayout, FVector2D(StartLocation.X, StartLocation.Y));
	FHex Neighbor = UGridFunctionLibrary::hex_neighbor(CurrentHex, Direction);
	FVector2D WorldPos2D = UGridFunctionLibrary::hex_to_pixel(GridLayout, Neighbor);
	return FVector2D(WorldPos2D.X, WorldPos2D.Y);
}

void AGrid::HandlePlayerMoveIntoHex(FVector Location, int32 TeamId)
{
	if (!HasAuthority())
	{
		return;
	}

	FHex Hex = UGridFunctionLibrary::pixel_to_hex_rounded(GridLayout, FVector2D(Location.X, Location.Y));
	if (FHex* FoundHex = MapContainer.Find(Hex))
	{
		FoundHex->Occupied = true;
		FoundHex->TeamId = TeamId;
		Multicast_UpdateHexTeam(FoundHex->Index, TeamId);
	}
	else
	{
		UE_LOG(LogGrid, Warning, TEXT("Hex not found in MapContainer for player move"));
		return;

	}
}

bool AGrid::TryEnterHex(const FHex& CurrentHex, const FHex& Hex)
{
	if (FHex* FoundHex = MapContainer.Find(Hex))
	{
		if (FoundHex->OccupancyState != EOccupancyStates::Free)
		{
			return false;
		}
		FoundHex->OccupancyState = EOccupancyStates::Reserved;
		return true;
	}
	else
	{
		UE_LOG(LogGrid, Warning, TEXT("Hex not found in MapContainer for TryEnterHex"));
	}
	return false;
}

// For this I will eventually need to also verify that the previoushex has the pointer to the actor trying to occupy the new hex
bool AGrid::TryOccupyHex(const FHex& Hex, const FHex& PreviousHex)
{
	if (FHex* FoundHex = MapContainer.Find(Hex))
	{
		FoundHex->OccupancyState = EOccupancyStates::Occupied;
		if (FHex* FoundPreviousHex = MapContainer.Find(PreviousHex))
		{
			FoundPreviousHex->OccupancyState = EOccupancyStates::Free;
		}
		else
		{
			UE_LOG(LogGrid, Warning, TEXT("PreviousHex not found in MapContainer for TryOccupyHex"));
		}
		return true;
	}
	else
	{
		UE_LOG(LogGrid, Warning, TEXT("Hex not found in MapContainer for TryOccupyHex"));
	}
	return false;
}

void AGrid::Multicast_UpdateHexTeam_Implementation(int32 Index, int32 TeamId)
{
	GridHexagons->SetCustomDataValue(Index, 0, TeamId, true);
}




/* Grid Generation */ 

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
	GridHexagons->SetStaticMesh(HexagonMesh);
	GridHexagons->SetMaterial(0, HexagonMaterial);

	GridCenterCylinders->SetStaticMesh(CylinderMesh);
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

		

		// Or: spawn an actor/ISM instance at WorldPos
		const FTransform InstanceTransform = FTransform(FRotator::ZeroRotator, WorldPos);
		GridHexagons->AddInstanceWorldSpace(InstanceTransform);
	}
}

