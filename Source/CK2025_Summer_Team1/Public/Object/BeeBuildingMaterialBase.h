// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enumerations/BeeColorEnumerations.h"
#include "Object/BeeSelectableActorBase.h"
#include "BeeBuildingMaterialBase.generated.h"

/**
 * 
 */
UCLASS()
class CK2025_SUMMER_TEAM1_API ABeeBuildingMaterialBase : public ABeeSelectableActorBase
{
	GENERATED_BODY()

public:
	ABeeBuildingMaterialBase();

public:
	virtual void BeginPlay() override;

public:
	FORCEINLINE EBuildingMaterialBaseColor GetBuildingMaterialColor() const { return BuildingMaterialColor; }
	void SetBuildingMaterialColor(const EBuildingMaterialBaseColor NewColorEnum, FColor NewColor);
	
protected:
	virtual void NotifyActorOnClicked(FKey ButtonPressed = EKeys::LeftMouseButton) override;
	virtual void NotifyActorOnReleased(FKey ButtonReleased = EKeys::LeftMouseButton) override;

protected:
	virtual void ReturnSpawnedPoint();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	EBuildingMaterialBaseColor BuildingMaterialColor = EBuildingMaterialBaseColor::None;
	
	FVector SpawnedPoint;
};
