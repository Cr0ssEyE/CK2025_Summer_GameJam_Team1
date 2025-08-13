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
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	
	GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + FVector(0.f, 0.f, -1000.f),
		FQuat::Identity,
		ECC_TRACE_PUZZLE_OBJECT,
		FCollisionShape::MakeSphere(100.f),
		CollisionParams
		);

	if (!IsValid(HitResult.GetActor()))
	{
		return;
	}
	
	if (ABeeBuildingMaterialPollen* PollenObject = Cast<ABeeBuildingMaterialPollen>(HitResult.GetActor()))
	{
		TryMixingColor(PollenObject);
		return;
	}

	if (ABeeBuildingMaterialBeeswax* BeeswaxObject = Cast<ABeeBuildingMaterialBeeswax>(HitResult.GetActor()))
	{
		TryMixingColor(BeeswaxObject);
	}
}

void ABeeBuildingMaterialPollen::TryMixingColor(ABeeBuildingMaterialBase* OtherBuildingMaterial)
{
	EBuildingMaterialBaseColor MixedColor = EBuildingMaterialBaseColor::None;
	bool IsCanMixingColor = FBeeColorEnumHelper::FindMixedColor(BuildingMaterialColor, OtherBuildingMaterial->GetBuildingMaterialColor(), MixedColor);
	if (IsCanMixingColor)
	{
		GetGameInstance()->GetSubsystem<UBeePuzzleManageSubsystem>()->ChangeBuildingMaterialColor(OtherBuildingMaterial, MixedColor);
		if (auto Beeswax = Cast<ABeeBuildingMaterialBeeswax>(OtherBuildingMaterial))
		{
			if (Beeswax->IsOnPuzzlePlace())
			{
				GetGameInstance()->GetSubsystem<UBeePuzzleManageSubsystem>()->OnBeeswaxPlacedOnBoard.Broadcast();
			}
		}
		
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
	}
	SetActorLocation(LastPlacedPoint);
}

