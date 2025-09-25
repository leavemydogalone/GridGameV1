// Copyright Leavemydogalone


#include "Player/GridPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Character/GridV1CharacterBase.h"
#include "Grid/GridFunctionLibrary.h"
#include "Input/GridV1InputConfig.h"
#include "Grid/Data/GridTypes.h"
#include "GridV1GameplayTags.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
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

	/*for (const FGridV1InputAction& Action : InputConfig->AbilityInputActions)
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
	}*/

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

void AGridPlayerController::HandleMoveInput(const FInputActionValue& InputActionValue)
{
	AGridV1CharacterBase* Char = Cast<AGridV1CharacterBase>(GetPawn());
	if (!Char) return;

	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

	// Will need to account for camera rotation here later

	if (!bCanMove) return;

	if (!bMovementInputBuffered)
	{
		BufferedMovementInput = InputAxisVector;
		bMovementInputBuffered = true;

		GetWorld()->GetTimerManager().SetTimer(
			MovementInputBufferHandle,
			this,
			&AGridPlayerController::ResolveBufferedInput,
			MovementInputBufferTime,
			false
		);
	}
	else
	{
		BufferedMovementInput += InputAxisVector;
	}

}

void AGridPlayerController::ResolveBufferedInput()
{
	bMovementInputBuffered = false;

	// Normalize to -1/0/1 per axis
	int X = FMath::Clamp(FMath::RoundToInt(BufferedMovementInput.X), -1, 1);
	int Y = FMath::Clamp(FMath::RoundToInt(BufferedMovementInput.Y), -1, 1);

	EHexMoveType MoveType = ResolveHexInput(FVector2D(X, Y));

	if (MoveType != EHexMoveType::None)
	{
		ExecuteMove(MoveType);
		//StartMoveCooldown();
	}

	BufferedMovementInput = FVector2D::ZeroVector;
}

EHexMoveType AGridPlayerController::ResolveHexInput(FVector2D Input)
{
	int X = FMath::RoundToInt(Input.X);
	int Y = FMath::RoundToInt(Input.Y);

	if (Y > 0 && X == 0) return EHexMoveType::Forward;
	if (Y < 0 && X == 0) return EHexMoveType::Backward;
	if (Y > 0 && X < 0) return EHexMoveType::ForwardLeft;
	if (Y > 0 && X > 0) return EHexMoveType::ForwardRight;
	if (Y < 0 && X < 0) return EHexMoveType::BackwardLeft;
	if (Y < 0 && X > 0) return EHexMoveType::BackwardRight;

	// If only A or D, treat as rotation
	if (X < 0 && Y == 0) return EHexMoveType::RotateLeft;
	if (X > 0 && Y == 0) return EHexMoveType::RotateRight;

	return EHexMoveType::None;
}

void AGridPlayerController::ExecuteMove(EHexMoveType)
{
	// Get the hex in direction

	// Get current hex to then get the hex in provided direction


	//UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);


}
