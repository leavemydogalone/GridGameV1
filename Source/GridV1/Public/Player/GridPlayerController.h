// Copyright Leavemydogalone

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
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

	//void OnInputStarted();
	//void OnSetActionTriggered();
	//void OnSetActionReleased();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UGridV1InputConfig> InputConfig;

	void Move(const FInputActionValue& InputActionValue);

};
