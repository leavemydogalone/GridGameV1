 // Copyright Leavemydogalone


#include "Character/GridV1CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "Grid/GridFunctionLibrary.h"

AGridV1CharacterBase::AGridV1CharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	CurrentDirection = EHexDirection::None;
	Momentum = 0.f;
	BufferedInput = EHexDirection::None;

}
void AGridV1CharacterBase::BeginPlay()
{
	Super::BeginPlay();

}
void AGridV1CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentDirection == EHexDirection::None)
		return;

	FVector2D Dir2D = UGridFunctionLibrary::GetHexUnitVector(CurrentDirection);
	FVector Dir3D = FVector(Dir2D.X, Dir2D.Y, 0.f);

	// Scale speed by momentum
	GetCharacterMovement()->MaxWalkSpeed = BaseSpeed * FMath::Max(0.f, Momentum);

	// Apply input every frame
	AddMovementInput(Dir3D, 1.f);

	// Check hex center
	if (UGridFunctionLibrary::IsAtHexCenter(this))
	{
		ApplyBufferedInput();
	}
}
void AGridV1CharacterBase::HandleDirectionalInput(EHexDirection NewDirection)
{
	//I need this to take in the controller direction and handle directions based on that

	if (NewDirection == EHexDirection::None)
		return;

	if (UGridFunctionLibrary::IsAtHexCenter(this))
	{
		ServerSetDirection(NewDirection);
	}
	else
	{
		BufferedInput = NewDirection;
	}
}

void AGridV1CharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGridV1CharacterBase, CurrentDirection);
	DOREPLIFETIME(AGridV1CharacterBase, Momentum);
}

//bool AGridV1CharacterBase::IsAtHexCenter() const
//{
//	FVector Pos = GetActorLocation();
//	FVector Snapped = FVector(
//		FMath::GridSnap(Pos.X, 100.f),
//		FMath::GridSnap(Pos.Y, 100.f),
//		Pos.Z
//	);
//
//	return FVector::Dist2D(Pos, Snapped) < HexSnapRadius;
//}

void AGridV1CharacterBase::ApplyBufferedInput()
{
	if (BufferedInput != EHexDirection::None)
	{
		ServerSetDirection(BufferedInput);
		BufferedInput = EHexDirection::None;
	}
}

void AGridV1CharacterBase::ServerSetDirection_Implementation(EHexDirection NewDirection)
{
	FVector2D OldVec = UGridFunctionLibrary::GetHexUnitVector(CurrentDirection);
	FVector2D NewVec = UGridFunctionLibrary::GetHexUnitVector(NewDirection);

	float Angle = FMath::RadiansToDegrees(FMath::Acos(FVector2D::DotProduct(OldVec, NewVec)));

	if (CurrentDirection == EHexDirection::None)
	{
		Momentum = 1.f;
	}
	else if (Angle <= 60.f)
	{
		//Updated this
		Momentum = FMath::Max(MaxMomentum, Momentum + 0.5f);
	}
	else if (Angle <= 120.f)
	{
		Momentum = FMath::Max(1.f, Momentum - 0.5f);
	}
	else
	{
		Momentum = 1.f;
	}

	CurrentDirection = NewDirection;
	OnRep_MovementState();
}

void AGridV1CharacterBase::OnRep_MovementState()
{
	GetCharacterMovement()->MaxWalkSpeed = BaseSpeed * FMath::Max(0.f, Momentum);
}



