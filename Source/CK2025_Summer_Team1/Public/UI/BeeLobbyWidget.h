// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BeeLobbyWidget.generated.h"

class UBeeExitCheckWidget;
class UButton;

/**
 * 
 */
UCLASS()
class CK2025_SUMMER_TEAM1_API UBeeLobbyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	UFUNCTION(BlueprintCallable)
	void OnFadeInComplete();
	
	UFUNCTION(BlueprintCallable)
	void OnStartButtonClicked();

	UFUNCTION(BlueprintCallable)
	void OnExitButtonClicked();
	
	UFUNCTION(BlueprintCallable)
	void LoadStageMenuLevel();

	UFUNCTION(BlueprintCallable)
	void CloseExitCheckWidget();

	UFUNCTION(BlueprintCallable)
	void ExitGame();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> StartButton;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> ExitButton;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UBeeExitCheckWidget> ExitCheckWidget;
};
