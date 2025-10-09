// Copyright Leavemydogalone


#include "AbilitySystem/CustomAbilitySystemBPLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "AbilitySystem/AttributeSets/HealthAttributeSet.h"
#include "AbilitySystem/AttributeSets/ResistanceAttributeSet.h"
#include "AbilitySystem/Data/AbilitySystemData.h"


AActor* UCustomAbilitySystemBPLibrary::GetInstigatorFromGameplayEffectSpec(const FGameplayEffectSpec& Spec)
{
	return Spec.GetEffectContext().GetInstigator();
}

float UCustomAbilitySystemBPLibrary::GetAttributeValueFromActor(const AActor* const Actor, const FGameplayAttribute Attribute, const EAttributeSearchType SearchType)
{
	const UAbilitySystemComponent* const AbilitySystemComponent = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Actor);

	if (!AbilitySystemComponent)
	{
		return -1.f;
	}

	float ReturnValue = -1.0f;
	GetAttributeValue(AbilitySystemComponent, Attribute, SearchType, ReturnValue);

	return ReturnValue;
}

float UCustomAbilitySystemBPLibrary::GetAttributeValueFromAbilitySystem(const UAbilitySystemComponent* const AbilitySystemComponent, const FGameplayAttribute Attribute, const EAttributeSearchType SearchType)
{
	float ReturnValue = -1.0f;

	GetAttributeValue(AbilitySystemComponent, Attribute, SearchType, ReturnValue);

	return ReturnValue;
}

float UCustomAbilitySystemBPLibrary::CalculateEffectiveResistance(const float CurrentArmor)
{
	const float CurrentArmorTmp = FMath::Clamp(CurrentArmor, UResistanceAttributeSet::RESISTANCE_MIN, UResistanceAttributeSet::RESISTANCE_MAX);

	const float ArmorDenominator = UResistanceAttributeSet::RESISTANCE_BASE + CurrentArmorTmp;
	return UResistanceAttributeSet::RESISTANCE_BASE > 0.f && ArmorDenominator > 0.f ? UResistanceAttributeSet::RESISTANCE_BASE / ArmorDenominator : 1.f;
}

float UCustomAbilitySystemBPLibrary::GetValueAtLevel(const FScalableFloat& ScalableFloat, const float Level /* = 0.f */, const FString& ContextString /* = "" */)
{
	return ScalableFloat.GetValueAtLevel(Level, &ContextString);
}

void UCustomAbilitySystemBPLibrary::SetTargetOnGameplayEffectContext(FGameplayEffectContextHandle& ContextHandle, const AActor* TargetActor)
{
	if (FCustomGameplayEffectContext* const EffectContext = static_cast<FCustomGameplayEffectContext*>(ContextHandle.Get()))
	{
		EffectContext->SetTargetActor(TargetActor);
	}
}

void UCustomAbilitySystemBPLibrary::SetTargetOnGameplayEffectContextFromSpec(FGameplayEffectSpec& EffectSpec, const AActor* TargetActor)
{
	SetTargetOnGameplayEffectContext(const_cast<FGameplayEffectContextHandle&>(EffectSpec.GetEffectContext()), TargetActor);
}

const AActor* UCustomAbilitySystemBPLibrary::GetTargetActorFromGameplayEffectContext(const FGameplayEffectContextHandle& ContextHandle)
{
	if (const FCustomGameplayEffectContext* const EffectContext = static_cast<const FCustomGameplayEffectContext*>(ContextHandle.Get()))
	{
		return EffectContext->GetTargetActor();
	}
	return nullptr;
}

const AActor* UCustomAbilitySystemBPLibrary::GetTargetActorFromGameplayEffectSpec(const FGameplayEffectSpec& EffectSpec)
{
	return GetTargetActorFromGameplayEffectContext(EffectSpec.GetEffectContext());
}

void UCustomAbilitySystemBPLibrary::GetAttributeValue(const UAbilitySystemComponent* const AbilitySystemComponent, const FGameplayAttribute& Attribute, const EAttributeSearchType SearchType, OUT float& ReturnValue)
{
	ReturnValue = -1.0f;

	if (!AbilitySystemComponent || !AbilitySystemComponent->HasAttributeSetForAttribute(Attribute))
	{
		return;
	}

	switch (SearchType)
	{
	case EAttributeSearchType::FinalValue:
	{
		ReturnValue = AbilitySystemComponent->GetNumericAttribute(Attribute);

		return;
	}

	case EAttributeSearchType::BaseValue:
	{
		ReturnValue = AbilitySystemComponent->GetNumericAttributeBase(Attribute);

		return;
	}

	case EAttributeSearchType::BonusValue:
	{
		ReturnValue = AbilitySystemComponent->GetNumericAttribute(Attribute) - AbilitySystemComponent->
			GetNumericAttributeBase(Attribute);
	}
	}
}
