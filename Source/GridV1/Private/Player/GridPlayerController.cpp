// Copyright Leavemydogalone


#include "Player/GridPlayerController.h"
#include "Input/GridV1EnhancedInputComponent.h"

AGridPlayerController::AGridPlayerController()
{
}

void AGridPlayerController::BeginPlay()
{
}

void AGridPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UGridV1EnhancedInputComponent* GridV1EnhancedInputComponent = CastChecked<UGridV1EnhancedInputComponent>(InputComponent);
	GridV1EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGridPlayerController::Move);
}

void AGridPlayerController::Move(const FInputActionValue& InputActionValue)
{
}
