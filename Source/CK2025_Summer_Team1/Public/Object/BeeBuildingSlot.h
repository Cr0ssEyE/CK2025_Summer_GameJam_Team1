// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BillboardComponent.h"
#include "Enumerations/BeeColorEnumerations.h"
#include "GameFramework/Actor.h"
#include "BeeBuildingSlot.generated.h"

UCLASS()
class CK2025_SUMMER_TEAM1_API ABeeBuildingSlot : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABeeBuildingSlot();

public:
	FORCEINLINE FVector GetPuzzleCenterLocation() const { return PuzzleCenterComponent->GetComponentLocation(); }
	FORCEINLINE EBuildingMaterialBaseColor GetRequiredPieceColor() const { return RequiredPuzzlePieceColor; }
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<UStaticMeshComponent> MeshComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UBillboardComponent> PuzzleCenterComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle Slot", DisplayName = "퍼즐 조각 요구 색상")
	EBuildingMaterialBaseColor RequiredPuzzlePieceColor;
};
