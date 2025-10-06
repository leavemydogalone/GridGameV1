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


	//UFUNCTION(BlueprintCallable, Category = "Grid Character")
	//FVector GetCachedTargetLocation() const { return CachedTargetLocation; };

	virtual void Tick(float DeltaTime) override;


protected:
	virtual void BeginPlay() override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


private:
    
	UPROPERTY(ReplicatedUsing = OnRep_TargetHexCenter)
	FVector TargetHexCenter = FVector::ZeroVector;
	FVector CurrentHexCenter = FVector::ZeroVector;
	FVector CurrentDestination = FVector::ZeroVector;
	FVector2D CachedMovementTarget = FVector2D::ZeroVector;

	bool bIsMoving = false;

	UPROPERTY(ReplicatedUsing = OnRep_MovementScale, EditAnywhere, Category = "Grid | Movement")
	float MovementScale = 2.f;

	UPROPERTY(EditAnywhere, Category = "Grid | Movement")
	float SnapToCenterDistance = 15.f;

	//I am hard-coding it here but will need to make a getter from the grid later
	float DistanceBetweenHexCenters = 200.f;

	int32 TeamId = 1;

	void HandleMove();

	UFUNCTION(Server, Reliable)
	void Server_TryMoveIntoTargetHex();

	UFUNCTION()
	void OnRep_TargetHexCenter();

	UFUNCTION()
	void OnRep_MovementScale();

	//UFUNCTION(Server, Reliable)
	//void Server_TryMoveIntoNew();

	TScriptInterface<IGridInterface> GetGridInterface();

	UPROPERTY()
	TScriptInterface<IGridInterface> GridInterface;
};
