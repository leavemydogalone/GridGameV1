// Copyright Leavemydogalone

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Grid/Data/GridTypes.h"
#include "Interaction/GridInterface.h"
#include "GridV1CharacterBase.generated.h"

UCLASS()
class GRIDV1_API AGridV1CharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AGridV1CharacterBase();

	void HandleMovementDirectionInput(const int32 Direction);

	virtual void Tick(float DeltaTime) override;


protected:
	virtual void BeginPlay() override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


private:
    
	UPROPERTY(ReplicatedUsing = OnRep_TargetHexCenter)
	FVector TargetHexCenter = FVector::ZeroVector;

	UPROPERTY(Replicated)
	FHex TargetHex = FHex(0, 0, 0);

	UPROPERTY(Replicated)
	FVector CurrentHexCenter = FVector::ZeroVector;

	UPROPERTY(Replicated)
	FHex CurrentHex = FHex(0, 0, 0);

	bool bIsMoving = false;

	UPROPERTY(ReplicatedUsing = OnRep_MovementScale, EditAnywhere, Category = "Grid | Movement")
	float MovementScale = 2.f;

	UPROPERTY(EditAnywhere, Category = "Grid | Movement")
	float SnapToCenterDistance = 40.f;

	//I am hard-coding it here but will need to make a getter from the grid later
	float DistanceBetweenHexCenters = 200.f;

	int32 TeamId = 1;

	void HandleMove();

	UFUNCTION(Server, Reliable)
	void Server_TryMoveIntoTargetHex(const FHex& Hex);

	UFUNCTION(Server, Reliable)
	void Server_CompleteMoveIntoTargetHex(const FHex& Hex);

	UFUNCTION()
	void OnRep_TargetHexCenter();

	TScriptInterface<IGridInterface> GetGridInterface();

	UPROPERTY()
	TScriptInterface<IGridInterface> GridInterface;
};
