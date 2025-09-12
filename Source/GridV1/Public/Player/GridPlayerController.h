// Copyright Leavemydogalone

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Grid/Data/GridTypes.h"
#include "GridPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UGridV1InputConfig;


/**
 * 
 */
UCLASS()
class GRIDV1_API AGridPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AGridPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> GridV1MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

protected:
	//virtual void SetupInputComponent() override;
	virtual void BeginPlay();

	virtual void SetupInputComponent() override;



private:
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> GridV1Context;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UGridV1InputConfig> InputConfig;

	void Move(const FInputActionValue& InputActionValue);

	void HandleMoveInput(EHexDirection HexDirection);


	void MoveRight();
	void MoveLeft();
	void MoveUpRight();
	void MoveUpLeft();
	void MoveDownRight();
	void MoveDownLeft();


};
