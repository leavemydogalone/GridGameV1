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
    PreviousLocation = GetActorLocation();
    CachedTargetLocation = NewLocation;
}

void AGridV1CharacterBase::BeginPlay()
{
	Super::BeginPlay();

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

	HandleGridInteraction();

    const float Distance = FVector::Dist2D(GetActorLocation(), CachedTargetLocation);

    if (Distance < 5.f) // tolerance in Unreal units
    {
        // Snap exactly to target so drift doesn't accumulate
        SetActorLocation(CachedTargetLocation);
        CachedTargetLocation = FVector::ZeroVector;
        return;
    }

    FVector Direction = (CachedTargetLocation - GetActorLocation()).GetSafeNormal2D();
    AddMovementInput(Direction, 1.0f);
}

void AGridV1CharacterBase::HandleGridInteraction()
{
    //The below is buggy and skips some hexes if the player holds down input

	// See if actor is more than halfway between startinglocation and cachedtargetlocation
    if (FVector::Dist2D(GetActorLocation(), PreviousLocation) > FVector::Dist2D(CachedTargetLocation, PreviousLocation) / 2)
    {
        IGridInterface::Execute_HandlePlayerMoveIntoHex(UGridFunctionLibrary::GetGridManager(this), GetActorLocation(), TeamId);
    }
}
