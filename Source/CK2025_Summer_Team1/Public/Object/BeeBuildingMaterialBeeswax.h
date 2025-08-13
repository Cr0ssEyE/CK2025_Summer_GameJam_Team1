// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeeBuildingMaterialBase.h"
#include "BeeBuildingMaterialBeeswax.generated.h"

class UBeePuzzlePieceComponent;

UCLASS()
class CK2025_SUMMER_TEAM1_API ABeeBuildingMaterialBeeswax : public ABeeBuildingMaterialBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABeeBuildingMaterialBeeswax();

public:
	FORCEINLINE bool IsOnPuzzlePlace() const { return bIsOnPuzzlePlace; }
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorOnClicked(FKey ButtonPressed = EKeys::LeftMouseButton) override;
	virtual void NotifyActorOnReleased(FKey ButtonReleased = EKeys::LeftMouseButton) override;
	
protected:
	void CheckPuzzlePieceCanSnapToPlace();
	bool TrySnapPuzzlePieceToPlace();
	
protected:
	UPROPERTY(EditDefaultsOnly)
	TArray<UBeePuzzlePieceComponent*> PuzzlePieces;

	uint32 PuzzleMatchingCount;

	uint32 bIsOnPuzzlePlace : 1;
};
