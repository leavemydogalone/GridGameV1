// Copyright Leavemydogalone

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Grid/Data/GridTypes.h"
#include "GridV1CharacterBase.generated.h"

UCLASS()
class GRIDV1_API AGridV1CharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AGridV1CharacterBase();

	void SetCachedTargetLocation(const FVector& NewLocation);

	UFUNCTION(BlueprintCallable, Category = "Grid Character")
	FVector GetCachedTargetLocation() const { return CachedTargetLocation; };

	virtual void Tick(float DeltaTime) override;


protected:
	virtual void BeginPlay() override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


private:
    
	FVector CachedTargetLocation = FVector::ZeroVector;
	FVector PreviousHexCenterReached = FVector::ZeroVector;

	int32 TeamId = 1;

	void HandleMove();

	UFUNCTION(Server, Reliable)
	void Server_HandleGridInteraction();
};
