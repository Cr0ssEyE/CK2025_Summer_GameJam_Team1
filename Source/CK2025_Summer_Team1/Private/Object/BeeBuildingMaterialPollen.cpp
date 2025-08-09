// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/BeeBuildingMaterialPollen.h"

#include "K2Node_GetSubsystem.h"
#include "Constant/BeeCollisionNames.h"
#include "Game/BeePuzzleManageSubsystem.h"
#include "Object/BeeBuildingMaterialBeeswax.h"


// Sets default values
ABeeBuildingMaterialPollen::ABeeBuildingMaterialPollen()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABeeBuildingMaterialPollen::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABeeBuildingMaterialPollen::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);
}

void ABeeBuildingMaterialPollen::NotifyActorOnReleased(FKey ButtonReleased)
{
	Super::NotifyActorOnReleased(ButtonReleased);

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + FVector(0, 0, -1000),
		ECC_TRACE_PUZZLE_OBJECT
	);

	if (!IsValid(HitResult.GetActor()))
	{
		GetGameInstance()->GetSubsystem<UBeePuzzleManageSubsystem>()->OnPickUpObjectReleased.Broadcast();
		ReturnSpawnedPoint();
		return;
	}
	
	if (ABeeBuildingMaterialPollen* PollenObject = Cast<ABeeBuildingMaterialPollen>(HitResult.GetActor()))
	{
		return;
	}

	if (ABeeBuildingMaterialBeeswax* BeeswaxObject = Cast<ABeeBuildingMaterialBeeswax>(HitResult.GetActor()))
	{
		EBuildingMaterialBaseColor MixedColor = EBuildingMaterialBaseColor::None;
		bool IsCanMixingColor = FBeeColorEnumHelper::FindMixedColor(BuildingMaterialColor, BeeswaxObject->GetBuildingMaterialColor(), MixedColor);
		if (IsCanMixingColor)
		{
			GetGameInstance()->GetSubsystem<UBeePuzzleManageSubsystem>()->ChangeBuildingMaterialColor(BeeswaxObject, MixedColor);
			RootComponent->SetVisibility(false);
			ReturnSpawnedPoint();
		}
	}
}

