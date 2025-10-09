// Copyright Leavemydogalone

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Grid/Data/GridTypes.h"
#include "Interaction/GridInterface.h"
#include "AbilitySystem/Data/AbilitySystemData.h"
#include "AbilitySystemInterface.h"
#include "GridV1CharacterBase.generated.h"

class UCustomAbilitySystemComponent;

UCLASS(Abstract, NotBlueprintable)
class GRIDV1_API AGridV1CharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGridV1CharacterBase();

	void HandleMovementDirectionInput(const int32 Direction);

	virtual void Tick(float DeltaTime) override;


	// Implement the IAbilitySystemInterface. (This is used to find the Ability System Component.)
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintPure, Category = "Ability System")
	UCustomAbilitySystemComponent* GetCustomAbilitySystemComponent() const;

	void InitializeAbilitySystem();

	// This event is fired after Ability System Component initialization is finished.
	UFUNCTION(BlueprintNativeEvent)
	void PostInitializeAbilitySystem();

	UFUNCTION(BlueprintPure)
	const FAbilitySystemInitializationData& GetAbilitySystemInitializationData() const
	{
		return AbilitySystemInitializationData;
	}

protected:
	virtual void BeginPlay() override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Data used to initialize the Ability System Component. (Can be found in "AbilitySystemData.h")
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability System", Meta = (ShowOnlyInnerProperties))
	FAbilitySystemInitializationData AbilitySystemInitializationData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCustomAbilitySystemComponent> AbilitySystemComponent;

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_Controller() override;

private:
    
	UPROPERTY(ReplicatedUsing = OnRep_TargetHexCenter)
	FVector TargetHexCenter = FVector::ZeroVector;

	UPROPERTY(Replicated)
	FHex TargetHex = FHex(0, 0, 0);

	UPROPERTY(Replicated)
	FVector CurrentHexCenter = FVector::ZeroVector;

	UPROPERTY(Replicated)
	FHex CurrentHex = FHex(0, 0, 0);

	UPROPERTY(Replicated)
	bool bIsMoving = false;

	UPROPERTY(Replicated, EditAnywhere, Category = "Grid | Movement")
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
