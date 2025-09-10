// Copyright Leavemydogalone

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GridV1CharacterBase.generated.h"

UCLASS()
class GRIDV1_API AGridV1CharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGridV1CharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
