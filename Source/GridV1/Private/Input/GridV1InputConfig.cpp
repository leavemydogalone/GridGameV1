// Copyright Leavemydogalone

#include "Input/GridV1InputConfig.h"
#include "GameplayTagContainer.h"
#include "EnhancedInputSubsystems.h"

const UInputAction* UGridV1InputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FGridV1InputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s], on InputConfig [%s]"), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}

//const FGameplayTag& UGridV1InputConfig::FindGameplayTagFromActionInput(const UInputAction* InputAction, bool bLogNotFound) const  
//{  
//   for (const FGridV1InputAction& Action : AbilityInputActions)  
//   {  
//       if (Action.InputTag.IsValid() && Action.InputAction == InputAction)  
//       {  
//           return Action.InputTag;  
//       }  
//   }  
//
//   if (bLogNotFound)  
//   {  
//       UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s], on InputConfig [%s]"), *InputAction->GetName(), *GetNameSafe(this));  
//   }  
//
//   static const FGameplayTag EmptyTag; // Use a static empty tag to return a valid reference.  
//   return EmptyTag;  
//}

