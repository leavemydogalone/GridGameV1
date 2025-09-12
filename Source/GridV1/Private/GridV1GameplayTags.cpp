// Fill out your copyright notice in the Description page of Project Settings.


#include "GridV1GameplayTags.h"

namespace NativeGameplayTags
{
	namespace GridTags
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Grid_Shape_Square, "Grid.Shape.Square", "A Gameplay Tag associated with the Square shaped grid.")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Grid_Shape_Hexagon, "Grid.Shape.Hexagon", "A Gameplay Tag associated with the Square shaped grid.")
	}

	namespace DirectionTags {
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Direction_None, "Direction.None", "A Gameplay Tag associated with no direction.")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Direction_Right, "Direction.Right", "A Gameplay Tag associated with the right direction.")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Direction_Left, "Direction.Left", "A Gameplay Tag associated with the left direction.")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Direction_UpRight, "Direction.UpRight", "A Gameplay Tag associated with the up-right direction.")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Direction_UpLeft, "Direction.UpLeft", "A Gameplay Tag associated with the up-left direction.")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Direction_DownRight, "Direction.DownRight", "A Gameplay Tag associated with the down-right direction.")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Direction_DownLeft, "Direction.DownLeft", "A Gameplay Tag associated with the down-left direction.")
	}
}