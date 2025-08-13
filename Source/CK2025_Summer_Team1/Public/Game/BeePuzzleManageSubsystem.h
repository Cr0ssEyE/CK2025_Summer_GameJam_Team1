// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enumerations/BeeColorEnumerations.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BeePuzzleManageSubsystem.generated.h"

class ABeeBuildingSlot;
class ABeeBuildingMaterialBase;
class UBeePuzzleObjectDataAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBeeswaxPlacedOnBoard);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFadeStateChanged, const bool, bIsFadeIn);

USTRUCT(BlueprintType)
struct FBeeBuildingMaterialEventInfo
{
	GENERATED_BODY()
public:
	FBeeBuildingMaterialEventInfo():
	EffectedMaterialLastPlacedPoint(FVector::ZeroVector),
	RemovedMaterialLastPlacedPoint(FVector::ZeroVector)
	{
		
	}
public:
	UPROPERTY()
	TWeakObjectPtr<ABeeBuildingMaterialBase> EffectedBuildingMaterial;

	UPROPERTY()
	TWeakObjectPtr<ABeeBuildingMaterialBase> RemovedBuildingMaterial;

	FVector EffectedMaterialLastPlacedPoint;

	FVector RemovedMaterialLastPlacedPoint;
};

/**
 * 
 */
UCLASS()
class CK2025_SUMMER_TEAM1_API UBeePuzzleManageSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UBeePuzzleManageSubsystem();
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

public:
	FORCEINLINE virtual void RegisterPuzzleSlot(ABeeBuildingSlot* PuzzleSlot)
	{ 
		if (PuzzleSlot && !PuzzleSlots.Contains(PuzzleSlot))
		{
			PuzzleSlots.Add(PuzzleSlot);
		}
	}
	
	FORCEINLINE virtual void UnregisterPuzzleSlot(ABeeBuildingSlot* PuzzleSlot)
	{ 
		if (PuzzleSlot && PuzzleSlots.Contains(PuzzleSlot))
		{
			PuzzleSlots.Remove(PuzzleSlot);
		}
	}

	UFUNCTION()
	virtual void ChangeBuildingMaterialColor(ABeeBuildingMaterialBase* BuildingMaterial, const EBuildingMaterialBaseColor NewColor);
	
	UFUNCTION(BlueprintCallable)
	virtual void CheckPuzzleColorIsMatching();
	
public:
	FOnBeeswaxPlacedOnBoard OnBeeswaxPlacedOnBoard;
	FOnFadeStateChanged OnFadeStateChanged;
	
protected:
	UPROPERTY()
	TObjectPtr<UBeePuzzleObjectDataAsset> PuzzleDataAsset;

	UPROPERTY()
	TArray<ABeeBuildingSlot*> PuzzleSlots;
};
