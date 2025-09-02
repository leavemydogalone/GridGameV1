// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/Data/GridShapeInfo.h"

FGridShapeData UGridShapeInfo::FindGridInfoForTag(const FGameplayTag& GridTag, bool bLogNotFound) const
{
	for (const FGridShapeData& Info : GridInformation)
	{
		if (Info.GridTag == GridTag)
		{
			return Info;
		}
	}

	if (bLogNotFound)
	{
		/*UE_LOG(, Error, TEXT("Can't find info for AbilityTag [%s] on AbilityInfo [%s]"), *AbilityTag.ToString(), *GetNameSafe(this));*/
	}

	return FGridShapeData();
}
