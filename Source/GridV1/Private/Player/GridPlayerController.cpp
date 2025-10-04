// Copyright Leavemydogalone


#include "Player/GridPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Character/GridV1CharacterBase.h"
#include "Grid/GridFunctionLibrary.h"
#include "Input/GridV1InputConfig.h"
#include "Grid/Data/GridTypes.h"
#include "GridV1GameplayTags.h"
#include "Interaction/GridInterface.h"
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

	GridV1EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AGridPlayerController::HandleMoveInput);

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

void AGridPlayerController::ExecuteMove(EHexMoveType MoveType)
{
	if (AGridV1CharacterBase* ControlledPawn = GetPawn<AGridV1CharacterBase>())
	{
		FRotator Rotation = GetControlRotation();

		const IGridInterface* GridManager = Cast<IGridInterface>(UGridFunctionLibrary::GetGridManager(ControlledPawn));

		if (!GridManager) return;

		int32 Direction = FMath::FloorToInt(Rotation.Yaw / 60.f);

		//FHex HexDirection = UGridFunctionLibrary::hex_directions[RotationToMovementDirection];
		
		switch (MoveType)
		{
		case EHexMoveType::RotateLeft:
			//Handle player rotation here
			return;
			break;

		case EHexMoveType::RotateRight:
			//Handle player rotation here
			return;

			break;
		case EHexMoveType::Forward:
			Direction += 0;
			break;
		case EHexMoveType::ForwardRight:
			Direction += 1;
			break;
		case EHexMoveType::BackwardRight:
			Direction += 2;
			break;
		case EHexMoveType::Backward:
			Direction += 3;
			break;
		case EHexMoveType::BackwardLeft:
			Direction += 4;
			break;
		case EHexMoveType::ForwardLeft:
			Direction += 5;
			break;
		default:
			break;
		}

		if (Direction >= 6) Direction -= 6;

		const FVector2D TargetLocation = IGridInterface::Execute_GetNextHexCenter(UGridFunctionLibrary::GetGridManager(ControlledPawn), ControlledPawn->GetActorLocation(), Direction);

		FVector ThreeDTarget = FVector(TargetLocation.X, TargetLocation.Y, ControlledPawn->GetActorLocation().Z);

		// Will need to convert this into a move on tick (until reaching destination) function later
		//UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, ThreeDTarget);

		ControlledPawn->SetCachedTargetLocation(ThreeDTarget);

		DrawDebugSphere(GetWorld(), ThreeDTarget, 50.f, 12, FColor::Red, false, 2.f);

	}


	// Get the rotation of the character
	// Get the desired movement cardinal direction based on character rotation and input
	// ex) if character is facing 0 degrees and input is forward right, direction is FHex(1, -1, 0)
	// 
	// Get the hex in direction

	// Get current hex to then get the hex in provided direction


	


}
