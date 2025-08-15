// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BeeSubMenuWidget.generated.h"

class UBeeExitCheckWidget;
class UBeeSettingWidget;
class UButton;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSubMenuClosedEvent);

/**
 * 
 */
UCLASS()
class CK2025_SUMMER_TEAM1_API UBeeSubMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	virtual FReply NativeOnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;

public:
	FOnSubMenuClosedEvent OnSubMenuClosedEvent;
	
protected:
	UFUNCTION(BlueprintCallable)
	void OnReturnBtnClicked();
	
	UFUNCTION(BlueprintCallable)
	void OnExitBtnClicked();
	
	UFUNCTION(BlueprintCallable)
	void OnSettingBtnClicked();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> ReturnBtn;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> ExitBtn;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> SettingBtn;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UBeeSettingWidget> SettingWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UBeeExitCheckWidget> ExitCheckWidget;
};
