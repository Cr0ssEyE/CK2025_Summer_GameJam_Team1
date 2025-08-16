// Fill out your copyright notice in the Description page of Project Settings.


#include "Util/BeeCustomGameUserSetting.h"

UBeeCustomGameUserSetting::UBeeCustomGameUserSetting(const FObjectInitializer& ObjectInitializer):
	MasterSoundVolume(1),
	bMasterSoundIgnore(false)
{
	FrameRateLimit = 60.f;
}

UBeeCustomGameUserSetting* UBeeCustomGameUserSetting::GetCustomGameUserSettings()
{
	return CastChecked<UBeeCustomGameUserSetting>(GEngine->GetGameUserSettings());
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
