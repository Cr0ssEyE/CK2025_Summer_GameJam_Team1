// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BeePuzzleObjectDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class CK2025_SUMMER_TEAM1_API UBeePuzzleObjectDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Mesh", DisplayName = "스태틱 메시")
	TObjectPtr<UStaticMesh> ObjectMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Color", DisplayName = "기본 색상 1")
	FColor BaseFirstColor;
	
	UPROPERTY(EditDefaultsOnly, Category = "Color", DisplayName = "기본 색상 2")
	FColor BaseSecondColor;

	UPROPERTY(EditDefaultsOnly, Category = "Color", DisplayName = "기본 색상 3")
	FColor BaseThirdColor;

	UPROPERTY(EditDefaultsOnly, Category = "Color", DisplayName = "기본 색상 1과 2 혼합 색상")
	FColor MixFirstAndSecondColor;
	
	UPROPERTY(EditDefaultsOnly, Category = "Color", DisplayName = "기본 색상 1과 3 혼합 색상")
	FColor MixFirstAndThirdColor;

	UPROPERTY(EditDefaultsOnly, Category = "Color", DisplayName = "기본 색상 2과 3 혼합 색상")
	FColor MixSecondAndThirdColor;

	UPROPERTY(EditDefaultsOnly, Category = "Color", DisplayName = "기본 색상 1과 흰색 혼합 색상")
	FColor MixFirstAndWhiteColor;

	UPROPERTY(EditDefaultsOnly, Category = "Color", DisplayName = "기본 색상 2과 흰색 혼합 색상")
	FColor MixSecondAndWhiteColor;
	
	UPROPERTY(EditDefaultsOnly, Category = "Color", DisplayName = "기본 색상 3과 흰색 혼합 색상")
	FColor MixThirdAndWhiteColor;

	UPROPERTY(EditDefaultsOnly, Category = "Color", DisplayName = "기본 색상 1과 검은색 혼합 색상")
	FColor MixFirstAndBlackColor;

	UPROPERTY(EditDefaultsOnly, Category = "Color", DisplayName = "기본 색상 2과 검은색 혼합 색상")
	FColor MixSecondAndBlackColor;

	UPROPERTY(EditDefaultsOnly, Category = "Color", DisplayName = "기본 색상 3과 검은색 혼합 색상")
	FColor MixThirdAndBlackColor;
};
