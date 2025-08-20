// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/BeeStageInfoDataAsset.h"
#include "Enumerations/BeeColorEnumerations.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BeePuzzleManageSubsystem.generated.h"

class ABeeBuildingMaterialsGenerator;
class ABeePollenGenerator;
class ABeeBuildingSlot;
class ABeeBuildingMaterialBase;
class UBeePuzzleObjectDataAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBeeswaxPlacedOnBoard);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnColorMixed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPuzzleFinished);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFadeStateChanged, const bool, bIsFadeIn);

USTRUCT(BlueprintType)
struct FBeeBuildingMaterialEventInfo
{
	GENERATED_BODY()
public:
	FBeeBuildingMaterialEventInfo():
	EffectedMaterialBeforeColorEnum(EBuildingMaterialBaseColor::None),
	EffectedMaterialBeforeColor(FColor::White),
	EffectedMaterialLastPlacedPoint(FVector::ZeroVector),
	RemovedMaterialLastPlacedPoint(FVector::ZeroVector)
	{
		
	}

public:
	UPROPERTY()
	TObjectPtr<ABeeBuildingMaterialBase> EffectedBuildingMaterial;

	UPROPERTY()
	TObjectPtr<ABeeBuildingMaterialBase> RemovedBuildingMaterial;

	EBuildingMaterialBaseColor EffectedMaterialBeforeColorEnum;

	FColor EffectedMaterialBeforeColor;
	
	FVector EffectedMaterialLastPlacedPoint;

	FVector RemovedMaterialLastPlacedPoint;
};

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

	virtual FTransform GetSpawnPoint();
	virtual UBeeStageInfoDataAsset* GetStageData();
	virtual void ClearData();
	
public:
	UFUNCTION()
	virtual void RegisterPollenGenerator(ABeePollenGenerator* NewPollenGenerator);
	
	UFUNCTION()
	virtual void RegisterBeeswaxGenerator(ABeeBuildingMaterialsGenerator* NewBeeswaxGenerator);
	
	UFUNCTION()
	virtual void RegisterBuildingMaterialEventInfo(const FBeeBuildingMaterialEventInfo& EventInfo);

	UFUNCTION()
	virtual void ChangeBuildingMaterialColor(ABeeBuildingMaterialBase* BuildingMaterial, const EBuildingMaterialBaseColor NewColor);

	UFUNCTION()
	virtual bool UndoBuildingMaterialColorMixAction();
	
	UFUNCTION(BlueprintCallable)
	virtual void CheckPuzzleColorIsMatching();
	
	UFUNCTION(BlueprintCallable)
	void SetPollenCount();

public:
	FOnBeeswaxPlacedOnBoard OnBeeswaxPlacedOnBoard;
	FOnColorMixed OnColorMixed;
	FOnPuzzleFinished OnPuzzleFinished;
	FOnFadeStateChanged OnFadeStateChanged;
	
protected:
	UPROPERTY()
	TArray<ABeePollenGenerator*> PollenGenerators;

	UPROPERTY()
	TObjectPtr<ABeeBuildingMaterialsGenerator> BeeswaxGenerator;
	
	UPROPERTY()
	TObjectPtr<UBeePuzzleObjectDataAsset> PuzzleDataAsset;

	UPROPERTY()
	TObjectPtr<UBeeStageInfoDataAsset> StageInfoDataAsset;
	
	UPROPERTY()
	TArray<ABeeBuildingSlot*> PuzzleSlots;

	UPROPERTY()
	TArray<FBeeBuildingMaterialEventInfo> BuildingMaterialEventInfos;
};
