// Copyright Leavemydogalone

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Grid/Data/GridTypes.h"
#include "GridV1CharacterBase.generated.h"

UCLASS()
class GRIDV1_API AGridV1CharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	AGridV1CharacterBase();

	virtual void Tick(float DeltaTime) override;


protected:
	virtual void BeginPlay() override;

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


private:
    

};
