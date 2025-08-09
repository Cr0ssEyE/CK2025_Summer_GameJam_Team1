// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BeePlayerDataAsset.generated.h"

class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class CK2025_SUMMER_TEAM1_API UBeePlayerDataAsset : public UDataAsset
{
	GENERATED_BODY()

	// 입력
public:
	UPROPERTY(EditDefaultsOnly, Category = "Input", DisplayName = "IMC")
	TObjectPtr<UInputMappingContext> PlayerInputMappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "Input", DisplayName = "마우스 홀드 액션")
	TObjectPtr<UInputAction> PlayerMouseHoldAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input", DisplayName = "마우스 클릭 액션")
	TObjectPtr<UInputAction> PlayerMouseClickAction;

	// 카메라
public:
	UPROPERTY(EditDefaultsOnly, Category = "Camera", DisplayName = "카메라 거리")
	float PlayerCameraDistance;
	
	UPROPERTY(EditDefaultsOnly, Category = "Camera", DisplayName = "카메라 각도")
	FRotator PlayerCameraRotation;

	// 시스템 관련
public:
	UPROPERTY(EditDefaultsOnly, Category = "Puzzle", DisplayName = "오브젝트 픽업 높이")
	float ObjectPickUpHeight;

	UPROPERTY(EditDefaultsOnly, Category = "Puzzle", DisplayName = "오브젝트 자동 맞춤 거리")
	float ObjectSnapRange;
};
