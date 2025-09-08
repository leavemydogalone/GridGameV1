 // Copyright Leavemydogalone


#include "Character/GridV1CharacterBase.h"

// Sets default values
AGridV1CharacterBase::AGridV1CharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGridV1CharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGridV1CharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGridV1CharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

