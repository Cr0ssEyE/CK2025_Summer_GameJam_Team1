// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BeeSettingWidget.h"

#include "Components/Button.h"
#include "Components/ComboBoxString.h"
#include "Components/ProgressBar.h"
#include "Components/Slider.h"
#include "Enumerations/BeeSettingEnumerations.h"
#include "GameFramework/GameUserSettings.h"
#include "Util/BeeCustomGameUserSetting.h"

void UBeeSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	CloseButton->OnClicked.AddDynamic(this, &UBeeSettingWidget::CloseSettingWidget);

	/*
	 * Resolution Setting
	 */
	ResolutionComboBox->ClearOptions();
	FResolutionValueHelper ResolutionValueHelper;
	UEnum* ResolutionEnum = FindObject<UEnum>(nullptr, *ResolutionValueHelper.EnumPath, true);
	for (auto ResolutionType : TEnumRange<EResolutionTypes>())
	{
		FString ResolutionString = ResolutionEnum->GetNameStringByValue(static_cast<int64>(ResolutionType));
		ResolutionString.Append(TEXT("("));
		ResolutionString.Append(ResolutionValueHelper.ResolutionValues[static_cast<uint8>(ResolutionType)].Key);
		ResolutionString.Append(TEXT("×"));	
		ResolutionString.Append(ResolutionValueHelper.ResolutionValues[static_cast<uint8>(ResolutionType)].Value);
		ResolutionString.Append(TEXT(")"));	
		
		ResolutionComboBox->AddOption(ResolutionString);
	}
	ResolutionComboBox->OnSelectionChanged.AddDynamic(this, &UBeeSettingWidget::ApplyResolutionType);
	
	UseFullScreenButton->OnClicked.AddDynamic(this, &UBeeSettingWidget::ApplyFullScreen);
	UseWindowButton->OnClicked.AddDynamic(this, &UBeeSettingWidget::ApplyWindowScreen);

	ResolutionComboBox->SetSelectedOption(UBeeCustomGameUserSetting::GetCustomGameUserSettings()->GetDisplayResolutionString());
	ResolutionComboBox->OnSelectionChanged.Broadcast(ResolutionComboBox->GetSelectedOption(),  ESelectInfo::Type::OnMouseClick);

	if (UBeeCustomGameUserSetting::GetCustomGameUserSettings()->GetFullscreenMode() == EWindowMode::WindowedFullscreen)
	{
		UseFullScreenButton->OnClicked.Broadcast();
	}
	else
	{
		UseWindowButton->OnClicked.Broadcast();
	}

	UBeeCustomGameUserSetting::GetCustomGameUserSettings()->SetFrameRateLimit(60.f);
	UBeeCustomGameUserSetting::GetCustomGameUserSettings()->SetVSyncEnabled(true);

	/*
	 * Sound Setting
	 */
	MasterSoundVolumeSlider->OnValueChanged.AddDynamic(this, &UBeeSettingWidget::ApplyMasterSliderValue);
	
	float MasterVolume = UBeeCustomGameUserSetting::GetCustomGameUserSettings()->GetMasterSoundVolume();
	MasterVolume = FMath::Clamp(MasterVolume, 0.f, 1.f);
	MasterSoundVolumeSlider->SetValue(MasterVolume);
	MasterSoundVolumeSlider->OnValueChanged.Broadcast(MasterSoundVolumeSlider->GetValue());
}

void UBeeSettingWidget::CloseSettingWidget()
{
	SetRenderScale(FVector2d::Zero());
	SetIsEnabled(false);
	GEngine->GetGameUserSettings()->ApplySettings(true);
}

void UBeeSettingWidget::ApplyResolutionType(FString ResolutionName, ESelectInfo::Type Info)
{
	if(ResolutionName.IsEmpty())
	{
		return;
	}
	
	FResolutionValueHelper ResolutionValueHelper;
	uint32 ScreenWidthValue = FCString::Atoi(*ResolutionValueHelper.ResolutionValues[ResolutionComboBox->GetSelectedIndex()].Key);
	uint32 ScreenHeightValue = FCString::Atoi(*ResolutionValueHelper.ResolutionValues[ResolutionComboBox->GetSelectedIndex()].Value);
	UBeeCustomGameUserSetting::GetCustomGameUserSettings()->SaveScreenResolutionString(ResolutionName);
	UBeeCustomGameUserSetting::GetCustomGameUserSettings()->SetScreenResolution(FIntPoint(ScreenWidthValue, ScreenHeightValue));
	UBeeCustomGameUserSetting::GetCustomGameUserSettings()->ApplySettings(false);
}

void UBeeSettingWidget::ApplyFullScreen()
{
	UseFullScreenButton->SetIsEnabled(false);
	UseWindowButton->SetIsEnabled(true);
	
	UBeeCustomGameUserSetting::GetCustomGameUserSettings()->SetFullscreenMode(EWindowMode::WindowedFullscreen);
	UBeeCustomGameUserSetting::GetCustomGameUserSettings()->ApplySettings(true);
	UBeeCustomGameUserSetting::GetCustomGameUserSettings()->ConfirmVideoMode();
}

void UBeeSettingWidget::ApplyWindowScreen()
{
	UseFullScreenButton->SetIsEnabled(true);
	UseWindowButton->SetIsEnabled(false);
	
	UBeeCustomGameUserSetting::GetCustomGameUserSettings()->SetFullscreenMode(EWindowMode::Windowed);
	UBeeCustomGameUserSetting::GetCustomGameUserSettings()->ApplySettings(true);
	UBeeCustomGameUserSetting::GetCustomGameUserSettings()->ConfirmVideoMode();
}

void UBeeSettingWidget::ApplyMasterSliderValue(const float Value)
{
	MasterVolumeProgressBar->SetPercent(Value);
	UBeeCustomGameUserSetting::GetCustomGameUserSettings()->SetMasterSoundVolume(Value);
}