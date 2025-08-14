// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UI/BeeFadeManageWidget.h"
#include "BeeGameInstance.generated.h"

class UBeeFadeManageWidget;
class UBeeSaveGameData;

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
	FORCEINLINE void FadeIn() const { FadeManageWidget->BeginFadeIn(); }
	FORCEINLINE FOnFadeCompleteEvent* GetOnFadeInCompleteDelegate() { return &FadeManageWidget->OnFadeInCompleteEvent; }
	
	FORCEINLINE void FadeOut() const { FadeManageWidget->BeginFadeOut(); }
	FORCEINLINE FOnFadeCompleteEvent* GetOnFadeOutCompleteDelegate() { return &FadeManageWidget->OnFadeOutCompleteEvent; }

	FORCEINLINE void SetLastClearedStageNumber(const int32 StageNumber) { LastClearedStageNumber = StageNumber; }
	FORCEINLINE int32 GetLastClearedStageNumber() const { return LastClearedStageNumber; }

	FORCEINLINE UBeeSaveGameData* GetCurrentSaveGameData() const { return CurrentSaveGameData; }
	
	void SaveCurrentSaveGameData();
	
	void CreateDefaultSaveSlot();

private:
	UPROPERTY()
	TObjectPtr<UBeeSaveGameData> CurrentSaveGameData;

	UPROPERTY()
	TObjectPtr<UBeeFadeManageWidget> FadeManageWidget;
	
	UPROPERTY()
	TSubclassOf<UBeeFadeManageWidget> FadeManageWidgetClass;

	UPROPERTY()
	int32 LastClearedStageNumber;
	
};
