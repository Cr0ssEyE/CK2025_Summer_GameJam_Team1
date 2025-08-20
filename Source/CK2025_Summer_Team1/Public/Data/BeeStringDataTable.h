// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BeeStringDataTable.generated.h"

UENUM(BlueprintType)
enum class ESpeakerTypes : uint8
{
	Player UMETA(DisplayName = "Player"),
	NPC UMETA(DisplayName = "NPC"),
	Other UMETA(DisplayName = "Other")
};

USTRUCT(BlueprintType)
struct FStringDataTable : public FTableRowBase
{
	GENERATED_BODY()

public:
	FStringDataTable() :
		StageNumber(0),
		IsClearStory(false),
		SpeakerType(ESpeakerTypes::Other),
		Speaker(""),
		Words("")
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", DisplayName = "스테이지 번호")
	int32 StageNumber;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", DisplayName = "클리어 여부")
	bool IsClearStory;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data", DisplayName = "화자 유형")
	ESpeakerTypes SpeakerType;
	
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
