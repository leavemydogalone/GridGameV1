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

    //Convert the direction into temporary target hex location
    CachedMovementTarget = GetGridInterface()->GetNextHexCenter(GetActorLocation(), Direction);

    DrawDebugSphere(GetWorld(), UGridFunctionLibrary::Convert2DTo3DActorHeight(CachedMovementTarget, GetActorLocation()), 50.f, 12, FColor::Red, false, 0.5f);

    Server_TryMoveIntoTargetHex();

}

void AGridV1CharacterBase::BeginPlay()
{
	Super::BeginPlay();

    const FVector2D HexLocation2D = GetGridInterface()->GetHexCenterAtLocation(GetActorLocation());
	CurrentHexCenter = FVector(HexLocation2D.X, HexLocation2D.Y, GetActorLocation().Z);
        
}

void AGridV1CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HandleMove();
}

void AGridV1CharacterBase::HandleMove()
{
    if (TargetHexCenter == FVector::ZeroVector || !bIsMoving)
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


void AGridV1CharacterBase::Server_TryMoveIntoTargetHex_Implementation()
{
    FHex CurrentHex = GetGridInterface()->GetHexAtLocation(UGridFunctionLibrary::Convert3DTo2D(GetActorLocation()));
    FHex TargetHex = GetGridInterface()->GetHexAtLocation(CachedMovementTarget);

    if (GetGridInterface())
    {
        if (GetGridInterface()->TryEnterHex(CurrentHex, TargetHex))
        {
            TargetHexCenter = UGridFunctionLibrary::Convert2DTo3DActorHeight(CachedMovementTarget, GetActorLocation());
			bIsMoving = true;
            OnRep_TargetHexCenter();
            CachedMovementTarget = FVector2D::ZeroVector;
        }
        else {
            CachedMovementTarget = FVector2D::ZeroVector;
        }
    }
}

void AGridV1CharacterBase::OnRep_TargetHexCenter()
{
    TargetHexCenter = UGridFunctionLibrary::Convert2DTo3DActorHeight(CachedMovementTarget, GetActorLocation());
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