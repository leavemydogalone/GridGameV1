// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid/Data/GridShapeInfo.h"

FGridInfo UGridShapeInfo::FindGridInfoForTag(const EGridShape& GridShape, bool bLogNotFound) const
{
	for (const FGridInfo& Info : GridInformation)
	{
		if (Info.GridShape == GridShape)
		{
			return Info;
		}
	}

	if (bLogNotFound)
	{
		/*UE_LOG(, Error, TEXT("Can't find info for AbilityTag [%s] on AbilityInfo [%s]"), *AbilityTag.ToString(), *GetNameSafe(this));*/
		UE_LOG(LogTemp, Warning, TEXT("Can't find info for UGridShapeInfo"));

	}

	return FGridInfo();
}
