// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeeBuildingMaterialBase.h"
#include "BeeBuildingMaterialPollen.generated.h"

UCLASS()
class CK2025_SUMMER_TEAM1_API ABeeBuildingMaterialPollen : public ABeeBuildingMaterialBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABeeBuildingMaterialPollen();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	virtual void NotifyActorOnClicked(FKey ButtonPressed = EKeys::LeftMouseButton) override;
	virtual void NotifyActorOnReleased(FKey ButtonReleased = EKeys::LeftMouseButton) override;

};
