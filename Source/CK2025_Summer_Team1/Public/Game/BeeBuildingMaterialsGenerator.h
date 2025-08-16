// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Object/Components/BeePuzzlePieceSpawnPoint.h"
#include "BeeBuildingMaterialsGenerator.generated.h"

class UBeeStageInfoDataAsset;
class UBeePuzzlePieceSpawnPoint;

UCLASS()
class CK2025_SUMMER_TEAM1_API ABeeBuildingMaterialsGenerator : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABeeBuildingMaterialsGenerator();

public:
	FORCEINLINE FTransform GetRandomSpawnPointLocation() const { return PuzzlePieceSpawnPoints[FMath::RandRange(0, PuzzlePieceSpawnPoints.Num() - 1)]->GetComponentTransform(); }
	FORCEINLINE UBeeStageInfoDataAsset* GetStageInfoDataAsset() const { return StageInfoDataAsset; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UFUNCTION(BlueprintCallable)
	virtual void OnFadeStateChanged(bool bIsFadingIn);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Generator", DisplayName = "퍼즐 조각 생성 위치")
	TArray<UBeePuzzlePieceSpawnPoint*> PuzzlePieceSpawnPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Generator", DisplayName = "스테이지 정보")
	TObjectPtr<UBeeStageInfoDataAsset> StageInfoDataAsset;
};
