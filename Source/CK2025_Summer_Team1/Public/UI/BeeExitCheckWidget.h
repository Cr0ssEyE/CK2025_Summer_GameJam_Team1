// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BeeExitCheckWidget.generated.h"

/**
 * 
 */
UCLASS()
class CK2025_SUMMER_TEAM1_API UBeeExitCheckWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	UFUNCTION(BlueprintCallable)
	void ExitConfirmButtonEvent();

	UFUNCTION(BlueprintCallable)
	void ExitCancelButtonEvent();

	UFUNCTION(BlueprintCallable)
	void CloseExitCheckWidget();
	
protected:
	
};
