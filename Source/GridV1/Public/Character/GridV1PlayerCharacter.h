// Copyright Leavemydogalone

#pragma once

#include "CoreMinimal.h"
#include "Character/GridV1CharacterBase.h"
#include "GridV1PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class GRIDV1_API AGridV1PlayerCharacter : public AGridV1CharacterBase
{
	GENERATED_BODY()

public:	
	AGridV1PlayerCharacter();

	virtual void Tick(float DeltaSeconds) override;

	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
};
