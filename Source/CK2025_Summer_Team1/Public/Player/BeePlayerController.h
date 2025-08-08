// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "GameFramework/PlayerController.h"
#include "BeePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ABeePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABeePlayerController();
	
private:
	void BeginPlay() override;
	void SetupInputComponent() override;

	// 입력 설정
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Input", meta=(AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category= "Input", meta=(AllowPrivateAccess = "true"))
	UInputAction* SelectClickAction;

	// 입력 처리 관련
protected:
	float ObjectSnapRange;
	
};
