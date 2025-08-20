// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "BeeCustomGameUserSetting.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class CK2025_SUMMER_TEAM1_API UBeeCustomGameUserSetting : public UGameUserSettings
{
	GENERATED_BODY()

public:
	UBeeCustomGameUserSetting(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	UFUNCTION(BlueprintCallable)
	static UBeeCustomGameUserSetting* GetCustomGameUserSettings();

	virtual void ApplySettings(bool bCheckForCommandLineOverrides) override;
	
	void ApplySoundSettings();

	virtual void SetToDefaults() override;
	
	// 사운드
public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetMasterSoundVolume() const { return MasterSoundVolume; }
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetMasterSoundVolume(float Value) { MasterSoundVolume = Value; }

	// 그래픽
public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE FString GetDisplayResolutionString() const { return DisplayResolution; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SaveScreenResolutionString(FString& Type) { DisplayResolution = Type; }

protected:
	UPROPERTY(Config, SaveGame)
	float MasterSoundVolume;
	
	UPROPERTY(Config, SaveGame)
	uint8 bMasterSoundIgnore : 1;

protected:
	UPROPERTY(Config, SaveGame)
	FString DisplayResolution;
};
