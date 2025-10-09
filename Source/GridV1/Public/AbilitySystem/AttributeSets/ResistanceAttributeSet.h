// Copyright Leavemydogalone

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AttributeSets/AttributeSetBase.h"
#include "ResistanceAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class GRIDV1_API UResistanceAttributeSet : public UAttributeSetBase
{
	GENERATED_BODY()
	
public:

	UResistanceAttributeSet();

	static float RESISTANCE_BASE;
	static float RESISTANCE_MAX;
	static float RESISTANCE_MIN;

	// Attribute Set Overrides.
	virtual void PostAttributeBaseChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) const override;

	virtual void ClampAttributes(const FGameplayAttribute& Attribute, float& NewValue) const override;

	// Set Attributes to replicate.
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Holds the current value for Resistance.
	UPROPERTY(BlueprintReadOnly, Category = "Resistance Attribute Set", ReplicatedUsing = OnRep_Resistance)
	FGameplayAttributeData Resistance;
	ATTRIBUTE_ACCESSORS(UResistanceAttributeSet, Resistance)

		UFUNCTION(BlueprintPure, Category = "Resistance Attribute Set")
	static float GetBaseResistance() { return RESISTANCE_BASE; }

	UFUNCTION(BlueprintPure, Category = "Resistance Attribute Set")
	static FVector2D GetMinMaxResistance() { return FVector2D(RESISTANCE_MIN, RESISTANCE_MAX); }

protected:

	UFUNCTION()
	virtual void OnRep_Resistance(const FGameplayAttributeData& OldValue);
};
