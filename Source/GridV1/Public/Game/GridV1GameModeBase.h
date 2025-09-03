// Copyright Leavemydogalone

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Grid/Data/GridShapeInfo.h"
#include "GridV1GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GRIDV1_API AGridV1GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AGridV1GameModeBase();

	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	TObjectPtr<UGridShapeInfo> GridInfo;

private:
	
};
