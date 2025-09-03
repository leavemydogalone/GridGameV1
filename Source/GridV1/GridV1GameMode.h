// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GridV1GameMode.generated.h"

UCLASS(minimalapi)
class AGridV1GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGridV1GameMode();

	UPROPERTY(EditDefaultsOnly, Category = "Grid")
	TObjectPtr<UDataAsset> GridInfo;

private:

};



