// Copyright Leavemydogalone

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "GridV1InputConfig.generated.h"

USTRUCT(BlueprintType)
struct FGridV1InputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly)
	FVector2D Direction = FVector2D();
};

class UInputAction;
/**
 * 
 */
UCLASS()
class GRIDV1_API UGridV1InputConfig : public UDataAsset
{
	GENERATED_BODY()

public:

	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;

	//const FGameplayTag& FindGameplayTagFromActionInput(const UInputAction* InputAction, bool bLogNotFound) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FGridV1InputAction> AbilityInputActions;


	
};
