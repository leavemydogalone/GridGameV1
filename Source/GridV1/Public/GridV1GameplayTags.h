// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/GameplayTags/Public/NativeGameplayTags.h"

namespace NativeGameplayTags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Effect_NoLevel);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Effect_Type_Cooldown);

	namespace CharacterTags
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_Type_PC);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Character_Type_NPC);
	}

	namespace GridTags
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Grid_Shape_Square);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Grid_Shape_Hexagon);

	}
	namespace DirectionTags
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Direction_None);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Direction_Right);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Direction_Left);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Direction_UpRight);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Direction_UpLeft);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Direction_DownRight);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Direction_DownLeft);
	}

	namespace BasicAttack
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_DamageType_DirectDamage);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Resistance_Modifier_DirectDamage);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Resistance_Ignore_DirectDamage);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Immunity_DirectDamage);
	}

	namespace State
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Max_Health);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Max_Stamina);

		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Blocked_Regen_Health);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_State_Blocked_Regen_Stamina);
	}

	namespace Statuses
	{

		// Status Example
		// -- Bleeding --
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Debuff_Bleeding);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_DamageType_Bleeding);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Immunity_Bleeding);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Resistance_Modifier_Bleeding);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Resistance_Ignore_Bleeding);
	}
}

