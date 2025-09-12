// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/GameplayTags/Public/NativeGameplayTags.h"

namespace NativeGameplayTags
{

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

}

