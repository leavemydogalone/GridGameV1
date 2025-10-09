// Copyright Leavemydogalone


#include "AbilitySystem/CustomAbilitySystemGlobals.h"

#include "AbilitySystem/Data/AbilitySystemData.h"

FGameplayEffectContext* UCustomAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FCustomGameplayEffectContext();
}

FGameplayAbilityActorInfo* UCustomAbilitySystemGlobals::AllocAbilityActorInfo() const
{
	return Super::AllocAbilityActorInfo();
}
