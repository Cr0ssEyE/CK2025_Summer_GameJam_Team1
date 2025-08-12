// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BeeStageInfoDataAsset.generated.h"

USTRUCT(BlueprintType)
struct FBeePuzzlePieceData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Puzzle Piece", DisplayName = "퍼즐 조각 블루프린트")
	TSubclassOf<AActor> PuzzlePieceBlueprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Puzzle Piece", DisplayName = "퍼즐 조각 갯수")
	int32 PuzzlePieceCount;
};

/**
 * 
 */
UCLASS()
class CK2025_SUMMER_TEAM1_API UBeeStageInfoDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stage Info", DisplayName = "스테이지 번호")
	int32 StageNumber;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stage Info", DisplayName = "퍼즐 조각 데이터")
	TArray<FBeePuzzlePieceData> PuzzlePieceDataArray;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stage Info", DisplayName = "꽃가루 색상 갯수")
	int32 PollenColorCount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stage Info", DisplayName = "흑백 색상 사용 여부")
	uint32 bUseBlackAndWhiteColor : 1;
};
