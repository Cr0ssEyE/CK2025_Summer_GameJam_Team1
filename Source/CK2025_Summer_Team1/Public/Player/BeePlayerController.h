// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "BeePlayerController.generated.h"

class UInputAction;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class ABeePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABeePlayerController();
	
	void BeginPlay() override;

protected:
	void SetupInputComponent() override;
	void SelectHoldStarted(const FInputActionValue& InputActionValue);
	void SelectHoldCompleted(const FInputActionValue& InputActionValue);
	void SelectClickStarted(const FInputActionValue& InputActionValue);
	void SelectClickCompleted(const FInputActionValue& InputActionValue);

protected:
	void PickupObjectMoveToMouseCursor();
	
	// 입력 설정
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Input", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Input", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MouseHoldAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Input", meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MouseClickAction;

	// 입력 처리 관련
protected:
	float ObjectPickUpHeight;
	
	float ObjectSnapRange;

	uint32 bIsObjectPickup : 1;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TWeakObjectPtr<AActor> PickUpObject;
};
