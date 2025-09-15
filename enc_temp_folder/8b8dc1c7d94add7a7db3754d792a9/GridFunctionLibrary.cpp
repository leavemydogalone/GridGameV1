// Copyright Leavemydogalone


#include "Grid/GridFunctionLibrary.h"
#include "Grid/Data/GridShapeInfo.h"
#include "Grid/Data/GridTypes.h"
#include "Game/GridV1GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GridV1/GridV1.h"
#include "GridV1GameplayTags.h"
#include "Engine/World.h"
#include "DeveloperSettings/GridV1DeveloperSettings.h"
#include "NativeGameplayTags.h"

UGridShapeInfo* UGridFunctionLibrary::GetGridInfo(const UObject* WorldContextObject)
{
	const AGridV1GameModeBase* GridV1GameModeBase = Cast<AGridV1GameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (GridV1GameModeBase == nullptr) 
	{
		UE_LOG(LogTemp, Warning, TEXT("UGridFunctionLibrary::GetGridInfo: GridV1GameModeBase is nullptr"));
		return nullptr;
	}
	return GridV1GameModeBase->GridInfo;


}

FVector UGridFunctionLibrary::SnapVectorToVector(FVector V1, FVector V2)
{
	float SnappedX = UKismetMathLibrary::GridSnap_Float(V1.X, V2.X);
	float SnappedY = UKismetMathLibrary::GridSnap_Float(V1.Y, V2.Y);
	float SnappedZ = UKismetMathLibrary::GridSnap_Float(V1.Z, V2.Z);

	return FVector(SnappedX, SnappedY, SnappedZ);
}

FVector UGridFunctionLibrary::SnapVectorToGrid(FVector InVector)
{
	const UGridV1DeveloperSettings* GridSettings = GetDefault<UGridV1DeveloperSettings>();

	return FVector(
		FMath::GridSnap(InVector.X, GridSettings->GridTileSize.X),
		FMath::GridSnap(InVector.Y, GridSettings->GridTileSize.Y),
		InVector.Z
	);
}

bool UGridFunctionLibrary::IsFloatEven(float InFloat)
{
	return FMath::IsNearlyZero(FMath::Fmod(InFloat, 2.0f));
}

FVector UGridFunctionLibrary::TraceForGround(FVector StartLocation, bool HitSomething, FVector GridTileSize, UObject* WorldContextObject)
{
	TArray<FHitResult> OutHits;
	FVector OutVector = FVector::ZeroVector;

	if (!WorldContextObject) return OutVector;

	UWorld* World = GEngine->GetWorldFromContextObjectChecked(WorldContextObject);

	if (WorldContextObject)
	{
		float ApproximateSizeOfTile = GridTileSize.X / 3;

		bool bHit = World->SweepMultiByChannel(
			/*OutHits=*/ OutHits,
			/*Start=*/ StartLocation + FVector(0.f, 0.f, 1000.f),
			/*End=*/ StartLocation - FVector(0.f, 0.f, 1000.f),
			/*Quat=*/ FQuat::Identity,
			/*TraceChannel=*/ ECC_Ground,
			/*CollisionShape=*/ FCollisionShape::MakeSphere(ApproximateSizeOfTile)
		);
		if (bHit)
		{
			// Example: return the first hit location
			OutVector = OutHits[0].ImpactPoint;
			HitSomething = OutHits.Num() > 0;
		}
	}

	//Note to self, in the video he uses the start locations x and y but uses the hit z
	//He also snaps the z to the grid

	return OutVector;
}

FVector2D UGridFunctionLibrary::GetHexUnitVector(EHexDirection Dir)
{
	switch (Dir)
	{
	case EHexDirection::Right:      return FVector2D(1, 0);
	case EHexDirection::Left:		return FVector2D(-1, 0);
	case EHexDirection::UpRight:	return FVector2D(0.5f, FMath::Sqrt(3.f) / 2.f);
	case EHexDirection::UpLeft:		return FVector2D(-0.5f, FMath::Sqrt(3.f) / 2.f);
	case EHexDirection::DownRight:	return FVector2D(0.5f, -FMath::Sqrt(3.f) / 2.f);
	case EHexDirection::DownLeft:	return FVector2D(-0.5f, -FMath::Sqrt(3.f) / 2.f);
	default:						return FVector2D::ZeroVector;
	}
}

bool UGridFunctionLibrary::IsAtHexCenter(const AActor* Actor)
{
	const UGridV1DeveloperSettings* GridSettings = GetDefault<UGridV1DeveloperSettings>();

	FVector Pos = Actor->GetActorLocation();
	FVector Snapped = FVector(
		FMath::GridSnap(Pos.X, GridSettings->GridTileSize.X),
		FMath::GridSnap(Pos.Y, GridSettings->GridTileSize.Y),
		Pos.Z
	);

	return FVector::Dist2D(Pos, Snapped) < GridSettings->GridCenterRadius;
}

FVector UGridFunctionLibrary::GetNextHexCenterInDirection(FVector StartLocation, const EHexDirection Direction)
{
	const UGridV1DeveloperSettings* GridSettings = GetDefault<UGridV1DeveloperSettings>();
	FVector GridTileSize = GridSettings->GridTileSize;

	float VerticalOffset =  0.75f;
	float HorizontalOffset =  0.5f;

	FVector InstanceLocation = FVector::ZeroVector;
	float DiagonalVerticalDistance = VerticalOffset * GridTileSize.X;
	float DiagonalHorizontalDistance = HorizontalOffset * GridTileSize.Y;


	switch (Direction)
	{
	case EHexDirection::Right:   
		InstanceLocation = FVector(
			StartLocation.X,
			StartLocation.Y + GridTileSize.Y,
			StartLocation.Z
		);
		break;

	case EHexDirection::Left:		
		InstanceLocation = FVector(
			StartLocation.X,
			StartLocation.Y - GridTileSize.Y,
			StartLocation.Z
		);
		break;

	case EHexDirection::UpRight:	
		InstanceLocation = FVector(
			StartLocation.X + DiagonalVerticalDistance,
			StartLocation.Y + DiagonalHorizontalDistance,
			StartLocation.Z
		);

		break;

	case EHexDirection::UpLeft:
		InstanceLocation = FVector(
			StartLocation.X + DiagonalVerticalDistance,
			StartLocation.Y - DiagonalHorizontalDistance,
			StartLocation.Z
		);

		break;

	case EHexDirection::DownRight:
		InstanceLocation = FVector(
			StartLocation.X - DiagonalVerticalDistance,
			StartLocation.Y + DiagonalHorizontalDistance,
			StartLocation.Z
		);
		break;

	case EHexDirection::DownLeft:
		InstanceLocation = FVector(
			StartLocation.X - DiagonalVerticalDistance,
			StartLocation.Y - DiagonalHorizontalDistance,
			StartLocation.Z
		);
		break;

	default:						
		break;
	}
	return InstanceLocation;

}

//FVector2D UGridFunctionLibrary::GetDirectionFromGameplayTag(FGameplayTag& GameplayTag)
//{
//	if (GameplayTag.MatchesTagExact(NativeGameplayTags::DirectionTags::TAG_Direction_Right))
//	{
//		return GetHexUnitVector(EHexDirection::Right);
//	}
//	if (GameplayTag.MatchesTagExact(NativeGameplayTags::DirectionTags::TAG_Direction_Left))
//	{
//		return GetHexUnitVector(EHexDirection::Left);
//	}
//	if (GameplayTag.MatchesTagExact(NativeGameplayTags::DirectionTags::TAG_Direction_UpRight))
//	{
//		return GetHexUnitVector(EHexDirection::UpRight);
//	}
//	if (GameplayTag.MatchesTagExact(NativeGameplayTags::DirectionTags::TAG_Direction_UpLeft))
//	{
//		return GetHexUnitVector(EHexDirection::UpLeft);
//	}
//	if (GameplayTag.MatchesTagExact(NativeGameplayTags::DirectionTags::TAG_Direction_DownRight))
//	{
//		return GetHexUnitVector(EHexDirection::DownRight);
//	}
//	if (GameplayTag.MatchesTagExact(NativeGameplayTags::DirectionTags::TAG_Direction_DownLeft))
//	{
//		return GetHexUnitVector(EHexDirection::DownLeft);
//	}
//	return FVector2D::ZeroVector;
//}
