// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/BeePuzzleManageSubsystem.h"

#include "Constant/BeeAssetLocations.h"
#include "Data/BeePuzzleObjectDataAsset.h"
#include "Object/BeeBuildingMaterialBase.h"
#include "Util/BeeConstructorHelper.h"

UBeePuzzleManageSubsystem::UBeePuzzleManageSubsystem()
{
	PuzzleDataAsset = FBeeConstructorHelper::FindAndGetObject<UBeePuzzleObjectDataAsset>(LOCATION_COLOR_DATA, EAssertionLevel::Ensure);
}

void UBeePuzzleManageSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UBeePuzzleManageSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UBeePuzzleManageSubsystem::ChangeBuildingMaterialColor(ABeeBuildingMaterialBase* BuildingMaterial,
	const EBuildingMaterialBaseColor NewColor)
{
	FColor NewMaterialColor = FColor::Magenta;
	switch (NewColor)
	{
	case EBuildingMaterialBaseColor::BaseFirstColor:
		NewMaterialColor = PuzzleDataAsset->BaseFirstColor;
		break;
	case EBuildingMaterialBaseColor::BaseSecondColor:
		NewMaterialColor = PuzzleDataAsset->BaseSecondColor;
		break;
	case EBuildingMaterialBaseColor::BaseThirdColor:
		NewMaterialColor = PuzzleDataAsset->BaseThirdColor;
		break;
	case EBuildingMaterialBaseColor::MixFirstAndSecondColor:
		NewMaterialColor = PuzzleDataAsset->MixFirstAndSecondColor;
		break;
	case EBuildingMaterialBaseColor::MixFirstAndThirdColor:
		NewMaterialColor = PuzzleDataAsset->MixFirstAndThirdColor;
		break;
	case EBuildingMaterialBaseColor::MixSecondAndThirdColor:
		NewMaterialColor = PuzzleDataAsset->MixSecondAndThirdColor;
		break;
	case EBuildingMaterialBaseColor::White:
		NewMaterialColor = FColor::White;
		break;
	case EBuildingMaterialBaseColor::MixFirstAndWhiteColor:
		NewMaterialColor = PuzzleDataAsset->MixFirstAndWhiteColor;
		break;
	case EBuildingMaterialBaseColor::MixSecondAndWhiteColor:
		NewMaterialColor = PuzzleDataAsset->MixSecondAndWhiteColor;
		break;
	case EBuildingMaterialBaseColor::MixThirdAndWhiteColor:
		NewMaterialColor = PuzzleDataAsset->MixThirdAndWhiteColor;
		break;
	case EBuildingMaterialBaseColor::Black:
		NewMaterialColor = FColor::Black;
		break;
	case EBuildingMaterialBaseColor::MixFirstAndBlackColor:
		NewMaterialColor = PuzzleDataAsset->MixFirstAndBlackColor;
		break;
	case EBuildingMaterialBaseColor::MixSecondAndBlackColor:
		NewMaterialColor = PuzzleDataAsset->MixSecondAndBlackColor;
		break;
	case EBuildingMaterialBaseColor::MixThirdAndBlackColor:
		NewMaterialColor = PuzzleDataAsset->MixThirdAndBlackColor;
		break;
	default:
		checkNoEntry();
		break;
	}
	BuildingMaterial->SetBuildingMaterialColor(NewColor, NewMaterialColor);
}
