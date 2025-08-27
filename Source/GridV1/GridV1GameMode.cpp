// Copyright Epic Games, Inc. All Rights Reserved.

#include "GridV1GameMode.h"
#include "GridV1PlayerController.h"
#include "GridV1Character.h"
#include "UObject/ConstructorHelpers.h"

AGridV1GameMode::AGridV1GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AGridV1PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}