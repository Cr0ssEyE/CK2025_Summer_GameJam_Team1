// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UI/BeeFadeManageWidget.h"
#include "BeeGameInstance.generated.h"

class UBeeFadeManageWidget;
class UBeeSaveGameData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFadeWidgetEvent);

/**
 * 
 */
UCLASS()
class CK2025_SUMMER_TEAM1_API UBeeGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UBeeGameInstance();

public:
	virtual void Init() override;
	virtual void Shutdown() override;
	virtual void OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld) override;
	
public:
	FORCEINLINE void FadeIn() { FadeManageWidget->BeginFadeIn(); bIsFadeOnGoing = true; }
	FORCEINLINE void FadeOut() { FadeManageWidget->BeginFadeOut(); bIsFadeOnGoing = true; }
	FORCEINLINE void OnFadeComplete() { bIsFadeOnGoing = false; }

	FORCEINLINE bool IsFadeOnGoing() const { return bIsFadeOnGoing; }
	
	FOnFadeWidgetEvent FadeWidgetFadeInCompleteEvent;
	
	FOnFadeWidgetEvent FadeWidgetFadeOutCompleteEvent;
	
	FORCEINLINE void SetLastClearedStageNumber(const int32 StageNumber) { LastClearedStageNumber = StageNumber; }
	FORCEINLINE int32 GetLastClearedStageNumber() const { return LastClearedStageNumber; }

	FORCEINLINE void SetCurrentPlayingStageNumber(const int32 StageNumber) { CurrentPlayingStageNumber = StageNumber; }
	FORCEINLINE int32 GetCurrentPlayingStageNumber() const { return CurrentPlayingStageNumber; }
	
	FORCEINLINE UBeeSaveGameData* GetCurrentSaveGameData() const { return CurrentSaveGameData; }
	
	void SaveCurrentSaveGameData();
	
	void CreateDefaultSaveSlot();

	void OnPlayerSpawn(UBeeFadeManageWidget& PlayerFadeWidget);
	
private:
	UPROPERTY()
	TObjectPtr<UBeeSaveGameData> CurrentSaveGameData;

	UPROPERTY()
	TObjectPtr<UBeeFadeManageWidget> FadeManageWidget;
	
	UPROPERTY()
	int32 CurrentPlayingStageNumber;
	
	UPROPERTY()
	int32 LastClearedStageNumber;

	uint32 bIsFadeOnGoing : 1;
};
