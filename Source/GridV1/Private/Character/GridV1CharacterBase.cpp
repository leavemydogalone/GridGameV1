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


	// Scale speed by momentum
	GetCharacterMovement()->MaxWalkSpeed = BaseSpeed * FMath::Max(0.f, Momentum);

	// Apply input every frame

	// Check hex center

}
void AGridV1CharacterBase::HandleDirectionalInput(FRotator ControllerRotation, EHexDirection NewDirection)
{

	if (CharacterNorthRotatorSet == false)
	{
		CharacterNorthRotation = ControllerRotation;
		CharacterNorthRotatorSet = true;
	}

	const FVector NextHex = UGridFunctionLibrary::GetNextHexCenterInDirection(GetActorLocation(), NewDirection);

	//else
	//{
	//	BufferedInput = NewDirection;
	//}
}

void AGridV1CharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGridV1CharacterBase, CurrentDirection);
	DOREPLIFETIME(AGridV1CharacterBase, Momentum);
}


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
	//FVector2D OldVec = UGridFunctionLibrary::GetHexUnitVector(CurrentDirection);
	//FVector2D NewVec = UGridFunctionLibrary::GetHexUnitVector(NewDirection);

	//float Angle = FMath::RadiansToDegrees(FMath::Acos(FVector2D::DotProduct(OldVec, NewVec)));

	//if (CurrentDirection == EHexDirection::None)
	//{
	//	Momentum = 1.f;
	//}
	//else if (Angle <= 60.f)
	//{
	//	//Updated this
	//	Momentum = FMath::Max(MaxMomentum, Momentum + 0.5f);
	//}
	//else if (Angle <= 120.f)
	//{
	//	Momentum = FMath::Max(1.f, Momentum - 0.5f);
	//}
	//else
	//{
	//	Momentum = 1.f;
	//}

	//CurrentDirection = NewDirection;
	//OnRep_MovementState();
}

void AGridV1CharacterBase::OnRep_MovementState()
{
	GetCharacterMovement()->MaxWalkSpeed = BaseSpeed * FMath::Max(0.f, Momentum);
}



