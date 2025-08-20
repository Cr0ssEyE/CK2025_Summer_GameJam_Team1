// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "BeeSaveGameData.generated.h"

#define DEFAULT_FILE_NAME TEXT("DefaultSave")
#define DEFAULT_FILE_INDEX 0

/**
 * 
 */
UCLASS(BlueprintType)
class CK2025_SUMMER_TEAM1_API UBeeSaveGameData : public USaveGame
{
	GENERATED_BODY()

public:
	UBeeSaveGameData();

public:
	UPROPERTY(BlueprintReadWrite, Category = "SaveInfo")
	FString SaveFileName;

	UPROPERTY(BlueprintReadWrite, Category = "SaveInfo")
	int32 MaxClearedStageNumber;

	UPROPERTY(BlueprintReadWrite, Category = "SaveInfo")
	int32 LastClearedStageNumber;
};
