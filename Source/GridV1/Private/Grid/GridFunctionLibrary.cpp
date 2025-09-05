// Copyright Leavemydogalone


#include "Grid/GridFunctionLibrary.h"
#include "Grid/Data/GridShapeInfo.h"
#include "Game/GridV1GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


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
