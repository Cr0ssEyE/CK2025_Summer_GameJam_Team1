// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BeeStringDataTable.generated.h"

USTRUCT(BlueprintType)
struct FStringDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	FStringDataTable() :
	StageNumber(0),
	IsPlayer(true),
	Speaker(""),
	Words("")
	{
		
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", DisplayName = "스테이지 번호")
	int32 StageNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", DisplayName = "클리어 여부")
	bool IsClearStory;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", DisplayName = "플레이어 텍스트 여부")
	bool IsPlayer;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", DisplayName = "화자")
	FString Speaker;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", DisplayName = "내용")
	FString Words;
	
};

/**
 * 
 */
UCLASS()
class CK2025_SUMMER_TEAM1_API UBeeStringDataTable : public UDataTable
{
	GENERATED_BODY()
};
