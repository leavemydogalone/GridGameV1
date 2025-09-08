// Copyright Leavemydogalone


#include "Player/GridPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Input/GridV1EnhancedInputComponent.h"

AGridPlayerController::AGridPlayerController()
{
	bReplicates = true;
}

void AGridPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(GridV1Context);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem)
	{
		Subsystem->AddMappingContext(GridV1Context, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AGridPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UGridV1EnhancedInputComponent* GridV1EnhancedInputComponent = CastChecked<UGridV1EnhancedInputComponent>(InputComponent);
	GridV1EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGridPlayerController::Move);
	//UGridV1EnhancedInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void AGridPlayerController::Move(const FInputActionValue& InputActionValue)
{
	return;
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}
