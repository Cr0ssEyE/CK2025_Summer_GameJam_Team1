// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "BeeExitCheckWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonClickEvent);

/**
 * 
 */
UCLASS()
class CK2025_SUMMER_TEAM1_API UBeeExitCheckWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	FOnButtonClickEvent ConfirmButtonClickedEvent;
	FOnButtonClickEvent CancelButtonClickedEvent;
	
protected:
	UFUNCTION(BlueprintCallable)
	void OnConfirmButtonClicked();

	UFUNCTION(BlueprintCallable)
	void OnCancelButtonClicked();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> ConfirmBtn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> CancelBtn;
	
};
