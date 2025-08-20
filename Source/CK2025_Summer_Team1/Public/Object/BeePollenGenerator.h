// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BeeSelectableActorBase.h"
#include "Enumerations/BeeColorEnumerations.h"
#include "BeePollenGenerator.generated.h"

class ABeeBuildingMaterialPollen;

UCLASS()
class CK2025_SUMMER_TEAM1_API ABeePollenGenerator : public ABeeSelectableActorBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABeePollenGenerator();

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void SetPollenCount(int32 NewCount = 0) {  PollenCount = NewCount; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE EBuildingMaterialBaseColor GetPollenColorEnum() {  return BuildingMaterialColorEnum; }
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorOnClicked(FKey ButtonPressed = EKeys::LeftMouseButton) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UMaterialInstanceDynamic> InsideMaterialInstance;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TSubclassOf<ABeeBuildingMaterialPollen> PollenObject;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	EBuildingMaterialBaseColor BuildingMaterialColorEnum = EBuildingMaterialBaseColor::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	FColor BuildingMaterialColor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	int32 PollenCount;
};
