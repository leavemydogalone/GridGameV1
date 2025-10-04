 // Copyright Leavemydogalone


#include "Character/GridV1CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "Interaction/GridInterface.h"
#include "Grid/GridFunctionLibrary.h"

AGridV1CharacterBase::AGridV1CharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;


}

void AGridV1CharacterBase::SetCachedTargetLocation(const FVector& NewLocation)
{
    CachedTargetLocation = NewLocation;
}

void AGridV1CharacterBase::BeginPlay()
{
	Super::BeginPlay();

	PreviousHexCenterReached = GetActorLocation();
}

void AGridV1CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleMove();
}


void AGridV1CharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}

void AGridV1CharacterBase::HandleMove()
{
    if (CachedTargetLocation == FVector::ZeroVector)
    {
        return;
    }

	Server_HandleGridInteraction();

    const float Distance = FVector::Dist2D(GetActorLocation(), CachedTargetLocation);

    if (Distance < 5.f) // tolerance
    {
        // Snap exactly to target so drift doesn't accumulate
        SetActorLocation(CachedTargetLocation);
		PreviousHexCenterReached = CachedTargetLocation;
        CachedTargetLocation = FVector::ZeroVector;
        return;
    }

    FVector Direction = (CachedTargetLocation - GetActorLocation()).GetSafeNormal2D();
    AddMovementInput(Direction, 1.0f);
}

void AGridV1CharacterBase::Server_HandleGridInteraction_Implementation()
{
	// See if actor is more than halfway between startinglocation and cachedtargetlocation
    if (FVector::Dist2D(GetActorLocation(), PreviousHexCenterReached) > FVector::Dist2D(CachedTargetLocation, PreviousHexCenterReached) / 2)
    {
        IGridInterface::Execute_HandlePlayerMoveIntoHex(UGridFunctionLibrary::GetGridManager(this), GetActorLocation(), TeamId);
    }
}
