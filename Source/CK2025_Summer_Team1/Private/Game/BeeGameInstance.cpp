// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/BeeGameInstance.h"

#include "Constant/BeeAssetLocations.h"
#include "Kismet/GameplayStatics.h"
#include "UI/BeeFadeManageWidget.h"
#include "Util/BeeSaveGameData.h"

UBeeGameInstance::UBeeGameInstance():
CurrentPlayingStageNumber(0),
LastClearedStageNumber(0)
{
	
}

void UBeeGameInstance::Init()
{
	Super::Init();

	if (IsValid(CurrentSaveGameData))
	{
		SaveCurrentSaveGameData();
	}
	
	if (!IsValid(CurrentSaveGameData))
	{
		CurrentSaveGameData = Cast<UBeeSaveGameData>(UGameplayStatics::LoadGameFromSlot(DEFAULT_FILE_NAME, DEFAULT_FILE_INDEX));
		if (!IsValid(CurrentSaveGameData))
		{
			CreateDefaultSaveSlot();
		}
	}
}

void UBeeGameInstance::Shutdown()
{
	Super::Shutdown();
}

void UBeeGameInstance::OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld)
{
	Super::OnWorldChanged(OldWorld, NewWorld);

}

void UBeeGameInstance::SaveCurrentSaveGameData()
{
	if (IsValid(CurrentSaveGameData))
	{
		FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
		// 핫-하 하드코딩 빔
		if (CurrentLevelName != LEVEL_NAME_STAGE_ONE &&
			CurrentLevelName != LEVEL_NAME_STAGE_TWO &&
			CurrentLevelName != LEVEL_NAME_STAGE_THREE &&
			CurrentLevelName != LEVEL_NAME_STAGE_FOUR &&
			CurrentLevelName != LEVEL_NAME_STAGE_FIVE
			)
		{
			CurrentSaveGameData->MaxClearedStageNumber = LastClearedStageNumber;
		}
		
		CurrentSaveGameData->LastClearedStageNumber = LastClearedStageNumber;
		
		UGameplayStatics::SaveGameToSlot(CurrentSaveGameData,DEFAULT_FILE_NAME, DEFAULT_FILE_INDEX);
	}
}

void UBeeGameInstance::CreateDefaultSaveSlot()
{
	CurrentSaveGameData = nullptr;
	UBeeSaveGameData* NewData = Cast<UBeeSaveGameData>(UGameplayStatics::CreateSaveGameObject(UBeeSaveGameData::StaticClass()));
	UGameplayStatics::SaveGameToSlot(NewData, DEFAULT_FILE_NAME, DEFAULT_FILE_INDEX);
	CurrentPlayingStageNumber = 0;
	LastClearedStageNumber = 0;

	CurrentSaveGameData = NewData;
}

void UBeeGameInstance::OnPlayerSpawn(UBeeFadeManageWidget& PlayerFadeWidget)
{
	Init();
	FadeManageWidget = PlayerFadeWidget;
}
