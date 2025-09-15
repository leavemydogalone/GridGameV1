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

	virtual void Tick(float DeltaTime) override;

    UPROPERTY(ReplicatedUsing = OnRep_MovementState)
    EHexDirection CurrentDirection;

    UPROPERTY(ReplicatedUsing = OnRep_MovementState)
    float Momentum;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float BaseSpeed = 600.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float MaxMomentum = 3.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
    float HexSnapRadius = 50.f;

    void HandleDirectionalInput(FRotator ControllerRotation, EHexDirection NewDirection);

protected:
	virtual void BeginPlay() override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    // Buffer input if not at center
    EHexDirection BufferedInput;

    // Helpers
    //bool IsAtHexCenter() const;
    void ApplyBufferedInput();

    UFUNCTION(Server, Reliable)
    void ServerSetDirection(EHexDirection NewDirection);

    UFUNCTION()
    void OnRep_MovementState();

    FRotator CharacterNorthRotation;
    bool CharacterNorthRotatorSet = false;

private:
    

};
