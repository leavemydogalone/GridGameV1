 // Copyright Leavemydogalone


#include "Character/GridV1CharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "Interaction/GridInterface.h"
#include "AbilitySystem/CustomAbilitySystemComponent.h"
#include "Grid/GridFunctionLibrary.h"

AGridV1CharacterBase::AGridV1CharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	// If the NetUpdateFrequency is too low, there will be a delay on Ability activation / Effect application on the client.
	SetNetUpdateFrequency(100.0f);

	// Create the Ability System Component sub-object.
	AbilitySystemComponent = CreateDefaultSubobject<UCustomAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
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


UAbilitySystemComponent* AGridV1CharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

UCustomAbilitySystemComponent* AGridV1CharacterBase::GetCustomAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

void AGridV1CharacterBase::InitializeAbilitySystem()
{
	if (!AbilitySystemComponent)
	{
		// Shouldn't happen, but if it is, return an error.
		return;
	}

	// Call the function on "Custom Ability System Component" to set up references and Init data. (Client)
	AbilitySystemComponent->InitializeAbilitySystemData(AbilitySystemInitializationData, this, this);


	//TODO
	/*AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UMovementAttributeSet::GetMovementSpeedMultiplierAttribute()).AddUObject(this, &ThisClass::MovementSpeedMultiplierChanged);*/

	PostInitializeAbilitySystem();
}

void AGridV1CharacterBase::PostInitializeAbilitySystem_Implementation()
{
	if (!AbilitySystemComponent)
	{
		return;
	}
}

void AGridV1CharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitializeAbilitySystem();
}

void AGridV1CharacterBase::OnRep_Controller()
{
	Super::OnRep_Controller();
	InitializeAbilitySystem();
}


// Start Movement

void AGridV1CharacterBase::HandleMovementDirectionInput(const int32 Direction)
{
	if (!GetGridInterface() || bIsMoving) return;

	CurrentHex = UGridFunctionLibrary::pixel_to_hex_rounded(GetGridInterface()->GetLayout(), UGridFunctionLibrary::Convert3DTo2D(GetActorLocation()));

	FHex DestinationHex = UGridFunctionLibrary::hex_neighbor(CurrentHex, Direction);

	Server_TryMoveIntoTargetHex(DestinationHex);

}

void AGridV1CharacterBase::HandleMove()
{
    if (TargetHexCenter != FVector::ZeroVector && bIsMoving)
    {
        const float Distance = FVector::Dist2D(GetActorLocation(), TargetHexCenter);

        //I don't think this is working as I'd like, will need to investigate some more
        if (Distance < DistanceBetweenHexCenters / 2)
		{
			MovementScale = 10.f;
		}

		if (Distance < SnapToCenterDistance)
		{
			if (HasAuthority() && bIsMoving)
			{
				Server_CompleteMoveIntoTargetHex_Implementation(TargetHex);
			}
			
		}

		FVector Direction = (TargetHexCenter - GetActorLocation()).GetSafeNormal2D();
		AddMovementInput(Direction, MovementScale);
	}
}

// This just reserves the hex
void AGridV1CharacterBase::Server_TryMoveIntoTargetHex_Implementation(const FHex& Hex)
{
    if (GetGridInterface())
    {
        if (GetGridInterface()->TryEnterHex(CurrentHex, Hex))
        {
			TargetHexCenter = UGridFunctionLibrary::Convert2DTo3DActorHeight(UGridFunctionLibrary::hex_to_pixel(GetGridInterface()->GetLayout(), Hex), GetActorLocation());
            TargetHex = Hex;
			bIsMoving = true;

        }
        else {
            
        }
    }
}

void AGridV1CharacterBase::Server_CompleteMoveIntoTargetHex_Implementation(const FHex& Hex)
{
	if (GetGridInterface())
	{
		if (GetGridInterface()->TryOccupyHex(Hex, CurrentHex))
		{
			CurrentHex = Hex;
			SetActorLocation(TargetHexCenter);
			MovementScale = 2.f;
			CurrentHexCenter = TargetHexCenter;
			TargetHexCenter = FVector::ZeroVector;
			bIsMoving = false;
			return;
		}
	}
}

void AGridV1CharacterBase::OnRep_TargetHexCenter()
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

// End Movement

void AGridV1CharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGridV1CharacterBase, TargetHexCenter);
	DOREPLIFETIME(AGridV1CharacterBase, CurrentHexCenter);
	DOREPLIFETIME(AGridV1CharacterBase, CurrentHex);
	DOREPLIFETIME(AGridV1CharacterBase, bIsMoving);
	DOREPLIFETIME(AGridV1CharacterBase, MovementScale);

}