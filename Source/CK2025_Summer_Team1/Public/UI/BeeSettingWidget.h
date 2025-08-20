// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BeeSettingWidget.generated.h"

class USlider;
class UProgressBar;
class UComboBoxString;
class UButton;
class UCanvasPanel;
/**
 * 
 */
UCLASS()
class CK2025_SUMMER_TEAM1_API UBeeSettingWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void CloseSettingWidget();

protected:
	UFUNCTION(BlueprintCallable)
	void ApplyResolutionType(FString ResolutionName, ESelectInfo::Type Info);

	UFUNCTION(BlueprintCallable)
	void ApplyFullScreen();

	UFUNCTION(BlueprintCallable)
	void ApplyWindowScreen();

protected:
	UFUNCTION(BlueprintCallable)
	void ApplyMasterSliderValue(const float Value);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UCanvasPanel> MainCanvasPanel;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UButton> CloseButton;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UComboBoxString> ResolutionComboBox;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> UseFullScreenButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> UseWindowButton;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<USlider> MasterSoundVolumeSlider;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UProgressBar> MasterVolumeProgressBar;
};
