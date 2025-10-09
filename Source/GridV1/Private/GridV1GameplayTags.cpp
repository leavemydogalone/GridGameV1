// Fill out your copyright notice in the Description page of Project Settings.


#include "GridV1GameplayTags.h"

namespace NativeGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Effect_NoLevel, "Effect.NoLevel", "This GE won't be leveled up or down. Base level will always be the same (upon granting it).")
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Effect_Type_Cooldown, "Effect.Type.Cooldown", "This is a cooldown GE")

	namespace GridTags
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Grid_Shape_Square, "Grid.Shape.Square", "A Gameplay Tag associated with the Square shaped grid.")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Grid_Shape_Hexagon, "Grid.Shape.Hexagon", "A Gameplay Tag associated with the Square shaped grid.")
	}

	namespace CharacterTags
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Character_Type_PC, "Character.Type.PlayerCharacter", "A Gameplay Tag applied to Characters that are controlled by a local player.")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Character_Type_NPC, "Character.Type.NonPlayerCharacter", "A Gameplay Tag applied to Characters that are AI controlled.")
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


	namespace BasicAttack
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_DamageType_DirectDamage, "DamageType.DirectDamage", "Basic Damage Type. Used to calculated Resistance to Basic Damage.")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Resistance_Modifier_DirectDamage, "Resistance.Modifier.DirectDamage", "Granting Resistance to basic Damage")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Resistance_Ignore_DirectDamage, "Resistance.Ignore.DirectDamage", "Ignore Resistance to basic Damage. Will deal true damage.")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Immunity_DirectDamage, "Immunity.DirectDamage", "Immune to DirectDamage");

	}

	namespace State
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Max_Health, "State.Max.Health", "Max Health reached")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Max_Stamina, "State.Max.Stamina", "Max Stamina reached")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Blocked_Regen_Health, "State.Blocked.Regeneration.Health", "Block Health regeneration.")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_State_Blocked_Regen_Stamina, "State.Blocked.Regeneration.Stamina", "Block Stamina regeneration.")

	}

	namespace Statuses
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Debuff_Bleeding, "Debuff.Bleeding", "Is Bleeding. Can be used to trigger more effects.")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_DamageType_Bleeding, "DamageType.Bleeding", "Bleeding Damage Type. Used to calculated Resistance to Bleeding Damage.")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Immunity_Bleeding, "Immunity.Bleeding", "Immune to Bleeding")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Resistance_Modifier_Bleeding, "Resistance.Modifier.Bleeding", "Granting Resistance to Bleeding")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Resistance_Ignore_Bleeding, "Resistance.Ignore.Bleeding", "Ignore Resistance to Bleeding. Will increase bleeding with the source value.")
	}
}