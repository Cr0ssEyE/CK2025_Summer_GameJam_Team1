// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enumerations/BeeColorEnumerations.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BeePuzzleManageSubsystem.generated.h"

class ABeeBuildingMaterialBase;
class UBeePuzzleObjectDataAsset;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPickUpObjectReleased);

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
	virtual void ChangeBuildingMaterialColor(ABeeBuildingMaterialBase* BuildingMaterial, const EBuildingMaterialBaseColor NewColor);
	
public:
	FOnPickUpObjectReleased OnPickUpObjectReleased;
	
protected:
	UPROPERTY()
	TObjectPtr<UBeePuzzleObjectDataAsset> PuzzleDataAsset;
};
