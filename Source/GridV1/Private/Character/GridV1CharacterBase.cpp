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

void AGridV1CharacterBase::HandleMovementDirectionInput(const int32 Direction)
{
    if (!GetGridInterface()) return;

    CurrentHex = UGridFunctionLibrary::pixel_to_hex_rounded(GetGridInterface()->GetLayout(), UGridFunctionLibrary::Convert3DTo2D(GetActorLocation()));

	FHex DestinationHex = UGridFunctionLibrary::hex_neighbor(CurrentHex, Direction);

    Server_TryMoveIntoTargetHex(DestinationHex);

}

void AGridV1CharacterBase::BeginPlay()
{
	Super::BeginPlay();

    CurrentHexCenter = UGridFunctionLibrary::Convert2DTo3DActorHeight(GetGridInterface()->GetHexCenterAtLocation(GetActorLocation()), GetActorLocation());
        
}

void AGridV1CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleMove();
}

void AGridV1CharacterBase::HandleMove()
{
    if (TargetHexCenter == FVector::ZeroVector)
    {
        return;
    }


    // Check the distance from the CurrentHex
        // if > 30 - half < half, check if can enter hex
            // bool GridManager->ActorTryEnterHex = reserve hex and return bool
                // 
        // if not, add movement input, maybe with higher scale

    // if cannot enter hex, set the target destination as currenthexcenter

    const float Distance = FVector::Dist2D(GetActorLocation(), TargetHexCenter);

    //if(Distance)


    if (Distance < SnapToCenterDistance) // tolerance
    {
        SetActorLocation(TargetHexCenter);
        CurrentHexCenter = TargetHexCenter;
        TargetHexCenter = FVector::ZeroVector;
		bIsMoving = false;
        return;
    }

    FVector Direction = (TargetHexCenter - GetActorLocation()).GetSafeNormal2D();
    AddMovementInput(Direction, MovementScale);
}


void AGridV1CharacterBase::Server_TryMoveIntoTargetHex_Implementation(const FHex& TargetHex)
{
    if (GetGridInterface())
    {
        if (GetGridInterface()->TryEnterHex(CurrentHex, TargetHex))
        {
			TargetHexCenter = UGridFunctionLibrary::Convert2DTo3DActorHeight(UGridFunctionLibrary::hex_to_pixel(GetGridInterface()->GetLayout(), TargetHex), GetActorLocation());
			bIsMoving = true;

        }
        else {

        }
    }
}

void AGridV1CharacterBase::OnRep_TargetHexCenter()
{
    //TargetHexCenter = UGridFunctionLibrary::Convert2DTo3DActorHeight(CachedMovementTarget, GetActorLocation());
    bIsMoving = true;
}

void AGridV1CharacterBase::OnRep_MovementScale()
{
}

TScriptInterface<IGridInterface> AGridV1CharacterBase::GetGridInterface()
{
    if (!GridInterface.GetObject())
    {
        if (UGridFunctionLibrary::GetGridManager(this)->Implements<UGridInterface>())
        {
            GridInterface.SetObject(UGridFunctionLibrary::GetGridManager(this));
            GridInterface.SetInterface(Cast<IGridInterface>(UGridFunctionLibrary::GetGridManager(this)));
        }
    }

    return GridInterface;
}

void AGridV1CharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGridV1CharacterBase, TargetHexCenter);
}