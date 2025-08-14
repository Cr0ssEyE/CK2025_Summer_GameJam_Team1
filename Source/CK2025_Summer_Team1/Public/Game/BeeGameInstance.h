// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BeeGameInstance.generated.h"

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
	
public:
	void CreateDefaultSaveSlot();

private:
	UPROPERTY()
	TObjectPtr<UBeeSaveGameData> CurrentSaveGameData;
};
