// Copyright Leavemydogalone


#include "Grid/GridFunctionLibrary.h"
#include "Grid/Data/GridShapeInfo.h"
#include "Game/GridV1GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "GridV1/GridV1.h"
#include "Engine/World.h"


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
