// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "BeePuzzleStageWidget.generated.h"

class UBeeSubMenuWidget;
/**
 * 
 */
UCLASS()
class CK2025_SUMMER_TEAM1_API UBeePuzzleStageWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	UFUNCTION(BlueprintCallable)
	void OpenSubMenu();

	UFUNCTION(BlueprintCallable)
	void RestartStage();
	
	UFUNCTION(BlueprintCallable)
	void UndoLastAction();

protected:
	UFUNCTION(BlueprintCallable)
	void OnColorMixed();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> OpenSubMenuBtn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> RestartBtn;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> UndoBtn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UBeeSubMenuWidget> SubMenuWidget;
};
