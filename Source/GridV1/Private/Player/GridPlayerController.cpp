// Copyright Leavemydogalone


#include "Player/GridPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Character/GridV1CharacterBase.h"
#include "Grid/GridFunctionLibrary.h"
#include "Input/GridV1InputConfig.h"
#include "GridV1GameplayTags.h"
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

	for (const FGridV1InputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (Action.InputTag == NativeGameplayTags::DirectionTags::TAG_Direction_Left)
			{
				GridV1EnhancedInputComponent->BindAction(Action.InputAction, ETriggerEvent::Triggered, this, &AGridPlayerController::MoveLeft);
			}
			else if (Action.InputTag == NativeGameplayTags::DirectionTags::TAG_Direction_Right)
			{
				GridV1EnhancedInputComponent->BindAction(Action.InputAction, ETriggerEvent::Triggered, this, &AGridPlayerController::MoveRight);
			}
			else if (Action.InputTag == NativeGameplayTags::DirectionTags::TAG_Direction_UpLeft)
			{
				GridV1EnhancedInputComponent->BindAction(Action.InputAction, ETriggerEvent::Triggered, this, &AGridPlayerController::MoveUpLeft);
			}
			else if (Action.InputTag == NativeGameplayTags::DirectionTags::TAG_Direction_UpRight)
			{
				GridV1EnhancedInputComponent->BindAction(Action.InputAction, ETriggerEvent::Triggered, this, &AGridPlayerController::MoveUpRight);
			}
			else if (Action.InputTag == NativeGameplayTags::DirectionTags::TAG_Direction_DownLeft)
			{
				GridV1EnhancedInputComponent->BindAction(Action.InputAction, ETriggerEvent::Triggered, this, &AGridPlayerController::MoveDownLeft);
			}
			else if (Action.InputTag == NativeGameplayTags::DirectionTags::TAG_Direction_DownRight)
			{
				GridV1EnhancedInputComponent->BindAction(Action.InputAction, ETriggerEvent::Triggered, this, &AGridPlayerController::MoveDownRight);
			}
		}
	}

}

void AGridPlayerController::Move(const FInputActionValue& InputActionValue)
{
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

void AGridPlayerController::HandleMoveInput(EHexDirection HexDirection)
{
	//FVector2D Axis = InputActionValue.Get<FVector2D>();

	AGridV1CharacterBase* Char = Cast<AGridV1CharacterBase>(GetPawn());
	if (!Char) return;

	//FGameplayTag DirectionTag = InputConfig->FindGameplayTagFromActionInput(InputActionValue);


	Char->HandleDirectionalInput(HexDirection);

}



void AGridPlayerController::MoveRight()
{
	HandleMoveInput(EHexDirection::Right);
}

void AGridPlayerController::MoveLeft()
{
	HandleMoveInput(EHexDirection::Left);
}

void AGridPlayerController::MoveUpRight()
{
	HandleMoveInput(EHexDirection::UpRight);
}

void AGridPlayerController::MoveUpLeft()
{
	HandleMoveInput(EHexDirection::UpLeft);
}

void AGridPlayerController::MoveDownRight()
{
	HandleMoveInput(EHexDirection::DownRight);
}

void AGridPlayerController::MoveDownLeft()
{
	HandleMoveInput(EHexDirection::DownLeft);
}
