// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/BeeBuildingMaterialBase.h"

#include "Constant/BeeCollisionNames.h"
#include "Constant/BeeMaterialParamNames.h"
#include "Game/BeeGameInstance.h"
#include "Game/BeePuzzleManageSubsystem.h"

ABeeBuildingMaterialBase::ABeeBuildingMaterialBase() :
SpawnedPoint(FVector::ZeroVector),
LastPlacedPoint(FVector::ZeroVector)
{
	MeshComponent->SetCollisionProfileName(CP_PUZZLE_OBJECT);
}

void ABeeBuildingMaterialBase::BeginPlay()
{
	Super::BeginPlay();

	SpawnedPoint = GetActorLocation();
	LastPlacedPoint = SpawnedPoint;
}

void ABeeBuildingMaterialBase::SetBuildingMaterialColor(const EBuildingMaterialBaseColor NewColorEnum, FColor NewColor, bool IsGenerateObject)
{
	BuildingMaterialColorEnum = NewColorEnum;
	BuildingMaterialColor = NewColor;
	
	if (MeshComponent)
	{
		MeshComponent->SetColorParameterValueOnMaterials(PARAM_PUZZLE_OBJECT_COLOR, NewColor);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MeshComponent is not valid in %s"), *GetName());
	}
}

void ABeeBuildingMaterialBase::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);
	if (bIsSelected)
	{
		OnBuildingMaterialReleased.Broadcast();
	}
	else
	{
		OnBuildingMaterialPicked.Broadcast();
	}
}

void ABeeBuildingMaterialBase::NotifyActorOnReleased(FKey ButtonReleased)
{
	Super::NotifyActorOnReleased(ButtonReleased);
	if (bIsSelected)
	{
		OnBuildingMaterialReleased.Broadcast();
	}
	else
	{
		OnBuildingMaterialPicked.Broadcast();
	}
}

void ABeeBuildingMaterialBase::ReturnSpawnedPoint()
{
	SetActorLocation(SpawnedPoint);
}
