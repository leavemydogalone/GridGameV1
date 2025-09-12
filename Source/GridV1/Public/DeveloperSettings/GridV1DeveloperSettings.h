// Copyright Leavemydogalone

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "GridV1DeveloperSettings.generated.h"

/**
 * 
 */
UCLASS(config = Game, DefaultConfig)
class GRIDV1_API UGridV1DeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UGridV1DeveloperSettings();

	UPROPERTY(EditAnywhere, Config, Category = "GridV1")
	FVector GridTileSize = FVector(300.f, 300.f, 300.f);

	UPROPERTY(EditAnywhere, Config, Category = "GridV1")
	float GridCenterRadius = 100.f;
};
