// Copyright Leavemydogalone


#include "Grid/GridFunctionLibrary.h"
#include "Grid/Data/GridShapeInfo.h"
#include "Game/GridV1GameModeBase.h"
#include "Kismet/GameplayStatics.h"


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
