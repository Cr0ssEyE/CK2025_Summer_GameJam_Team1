// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "BeePuzzlePieceComponent.generated.h"


class ABeeBuildingMaterialBeeswax;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CK2025_SUMMER_TEAM1_API UBeePuzzlePieceComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBeePuzzlePieceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
