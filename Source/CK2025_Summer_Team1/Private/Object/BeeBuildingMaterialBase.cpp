// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/BeeBuildingMaterialBase.h"

#include "Constant/BeeCollisionNames.h"
#include "Constant/BeeMaterialParamNames.h"

ABeeBuildingMaterialBase::ABeeBuildingMaterialBase() : SpawnedPoint(FVector::ZeroVector)
{
	MeshComponent->SetCollisionProfileName(CP_PUZZLE_OBJECT);
	
}

void ABeeBuildingMaterialBase::BeginPlay()
{
	Super::BeginPlay();

	SpawnedPoint = GetActorLocation();
}

void ABeeBuildingMaterialBase::SetBuildingMaterialColor(const EBuildingMaterialBaseColor NewColorEnum, FColor NewColor)
{
	BuildingMaterialColor = NewColorEnum;
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
}

void ABeeBuildingMaterialBase::NotifyActorOnReleased(FKey ButtonReleased)
{
	Super::NotifyActorOnReleased(ButtonReleased);
}

void ABeeBuildingMaterialBase::ReturnSpawnedPoint()
{
	SetActorLocation(SpawnedPoint);
}
