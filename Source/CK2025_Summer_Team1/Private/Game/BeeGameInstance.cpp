// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/BeeGameInstance.h"

#include "Kismet/GameplayStatics.h"
#include "Util/BeeSaveGameData.h"

UBeeGameInstance::UBeeGameInstance()
{
}

void UBeeGameInstance::Init()
{
	Super::Init();

	if (UBeeSaveGameData* SaveData = Cast<UBeeSaveGameData>(UGameplayStatics::LoadGameFromSlot(DEFAULT_FILE_NAME, DEFAULT_FILE_INDEX)))
	{
		CurrentSaveGameData = SaveData;
	}
}

void UBeeGameInstance::Shutdown()
{
	Super::Shutdown();
	if (IsValid(CurrentSaveGameData))
	{
		UGameplayStatics::SaveGameToSlot(CurrentSaveGameData,DEFAULT_FILE_NAME, DEFAULT_FILE_INDEX);
	}
}

void UBeeGameInstance::CreateDefaultSaveSlot()
{
	UBeeSaveGameData* NewData = Cast<UBeeSaveGameData>(UGameplayStatics::CreateSaveGameObject(UBeeSaveGameData::StaticClass()));
	UGameplayStatics::SaveGameToSlot(NewData, NewData->SaveFileName, 0);
}
