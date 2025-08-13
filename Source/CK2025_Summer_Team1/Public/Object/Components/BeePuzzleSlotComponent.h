// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BillboardComponent.h"
#include "Enumerations/BeeColorEnumerations.h"
#include "BeePuzzleSlotComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CK2025_SUMMER_TEAM1_API UBeePuzzleSlotComponent : public UBillboardComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBeePuzzleSlotComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle Slot", DisplayName = "퍼즐 조각 요구 색상")
	EBuildingMaterialBaseColor RequiredPuzzlePieceColor;
};
