// Fill out your copyright notice in the Description page of Project Settings.


#include "Util/BeeCustomGameUserSetting.h"

UBeeCustomGameUserSetting::UBeeCustomGameUserSetting(const FObjectInitializer& ObjectInitializer):
	MasterSoundVolume(1),
	bMasterSoundIgnore(false),
	DisplayResolution("HD(1280×720)")
{
	FrameRateLimit = 60.f;
}

UBeeCustomGameUserSetting* UBeeCustomGameUserSetting::GetCustomGameUserSettings()
{
	UBeeCustomGameUserSetting* CustomGameUserSettings = Cast<UBeeCustomGameUserSetting>(GEngine->GetGameUserSettings());
	if (CustomGameUserSettings)
	{
		return CustomGameUserSettings;
	}
	return Cast<UBeeCustomGameUserSetting>( GetGameUserSettings());
}

void UBeeCustomGameUserSetting::ApplySettings(bool bCheckForCommandLineOverrides)
{
	Super::ApplySettings(bCheckForCommandLineOverrides);
}

void UBeeCustomGameUserSetting::ApplySoundSettings()
{
	
}

void UBeeCustomGameUserSetting::SetToDefaults()
{
	Super::SetToDefaults();
	
	FrameRateLimit = 60.f;
}
