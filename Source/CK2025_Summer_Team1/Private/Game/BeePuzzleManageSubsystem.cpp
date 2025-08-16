// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/BeePuzzleManageSubsystem.h"

#include "Constant/BeeAssetLocations.h"
#include "Constant/BeeCollisionNames.h"
#include "Data/BeePuzzleObjectDataAsset.h"
#include "Game/BeeBuildingMaterialsGenerator.h"
#include "Game/BeeGameInstance.h"
#include "Object/BeeBuildingMaterialBase.h"
#include "Object/BeeBuildingMaterialBeeswax.h"
#include "Object/BeeBuildingSlot.h"
#include "Object/BeePollenGenerator.h"
#include "Util/BeeConstructorHelper.h"

UBeePuzzleManageSubsystem::UBeePuzzleManageSubsystem()
{
	PuzzleDataAsset = FBeeConstructorHelper::FindAndGetObject<UBeePuzzleObjectDataAsset>(LOCATION_COLOR_DATA, EAssertionLevel::Ensure);
}

void UBeePuzzleManageSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	OnBeeswaxPlacedOnBoard.AddDynamic(this, &UBeePuzzleManageSubsystem::CheckPuzzleColorIsMatching);
}

void UBeePuzzleManageSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

FTransform UBeePuzzleManageSubsystem::GetSpawnPoint()
{
	if (BeeswaxGenerator)
	{
		return BeeswaxGenerator->GetRandomSpawnPointLocation();
	}
	return FTransform::Identity;
}

UBeeStageInfoDataAsset* UBeePuzzleManageSubsystem::GetStageData()
{
	if (BeeswaxGenerator)
	{
		return StageInfoDataAsset;
	}

	return nullptr;
}

void UBeePuzzleManageSubsystem::ClearData()
{
	PollenGenerators.Empty();
	BeeswaxGenerator = nullptr;
}

void UBeePuzzleManageSubsystem::RegisterPollenGenerator(ABeePollenGenerator* NewPollenGenerator)
{
	if (NewPollenGenerator)
	{
		PollenGenerators.Add(NewPollenGenerator);
	}
}

void UBeePuzzleManageSubsystem::RegisterBeeswaxGenerator(ABeeBuildingMaterialsGenerator* NewBeeswaxGenerator)
{
	if (NewBeeswaxGenerator)
	{
		BeeswaxGenerator = NewBeeswaxGenerator;
		StageInfoDataAsset = BeeswaxGenerator->GetStageInfoDataAsset();
	}
}

void UBeePuzzleManageSubsystem::RegisterBuildingMaterialEventInfo(const FBeeBuildingMaterialEventInfo& EventInfo)
{
	if (IsValid(EventInfo.EffectedBuildingMaterial) && IsValid(EventInfo.RemovedBuildingMaterial))
	{
		BuildingMaterialEventInfos.Push(EventInfo);
	}
}

void UBeePuzzleManageSubsystem::ChangeBuildingMaterialColor(ABeeBuildingMaterialBase* BuildingMaterial, const EBuildingMaterialBaseColor NewColor)
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
	OnColorMixed.Broadcast();
}

bool UBeePuzzleManageSubsystem::UndoBuildingMaterialColorMixAction()
{
	if (BuildingMaterialEventInfos.IsEmpty())
	{
		return false;
	}
	
	FBeeBuildingMaterialEventInfo LastEventInfo = BuildingMaterialEventInfos.Pop();
	
	LastEventInfo.EffectedBuildingMaterial->SetActorLocation(LastEventInfo.EffectedMaterialLastPlacedPoint);
	LastEventInfo.EffectedBuildingMaterial->SetBuildingMaterialColor(LastEventInfo.EffectedMaterialBeforeColorEnum, LastEventInfo.EffectedMaterialBeforeColor);
	LastEventInfo.EffectedBuildingMaterial->SetLastPlacedPoint();
	
	LastEventInfo.RemovedBuildingMaterial->SetActorLocation(LastEventInfo.RemovedMaterialLastPlacedPoint);
	LastEventInfo.RemovedBuildingMaterial->SetActorHiddenInGame(false);
	LastEventInfo.RemovedBuildingMaterial->SetActorEnableCollision(true);
	LastEventInfo.RemovedBuildingMaterial->SetLastPlacedPoint();

	if (BuildingMaterialEventInfos.IsEmpty())
	{
		return false;
	}
	
	return true;
}

void UBeePuzzleManageSubsystem::CheckPuzzleColorIsMatching()
{
	for (const auto PuzzleSlot : PuzzleSlots)
	{
		if (!IsValid(PuzzleSlot))
		{
			continue;
		}

		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(PuzzleSlot);

		const FVector StartLocation = PuzzleSlot->GetPuzzleCenterLocation();
		
		GetWorld()->SweepSingleByChannel(
			HitResult,
			StartLocation,
			StartLocation,
			FQuat::Identity,
			ECC_TRACE_PUZZLE_OBJECT,
			FCollisionShape::MakeSphere(10.f),
			CollisionParams
		);

		if (!IsValid(HitResult.GetActor()))
		{
			return;
		}

		const ABeeBuildingMaterialBeeswax* BeeswaxObject = Cast<ABeeBuildingMaterialBeeswax>(HitResult.GetActor());
		if (!IsValid(BeeswaxObject))
		{
			return;
		}

		if (BeeswaxObject->GetBuildingMaterialColorEnum() != PuzzleSlot->GetRequiredPieceColor())
		{
			return;
		}
	}

	//TODO: 클리어 관련 처리 필요
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("All puzzle pieces are matched!"), false, FVector2D(3.f, 3.f));
	UBeeGameInstance* GameInstance = GetWorld()->GetGameInstanceChecked<UBeeGameInstance>();
	GameInstance->SetLastClearedStageNumber(GameInstance->GetCurrentPlayingStageNumber());
	PollenGenerators.Empty();
	BeeswaxGenerator = nullptr;
	OnPuzzleFinished.Broadcast();
}

void UBeePuzzleManageSubsystem::SetPollenCount()
{
	for (auto PollenGenerator : PollenGenerators)
	{
		if ((PollenGenerator->GetPollenColorEnum() == EBuildingMaterialBaseColor::Black || PollenGenerator->GetPollenColorEnum() == EBuildingMaterialBaseColor::White) && !StageInfoDataAsset->bUseBlackAndWhiteColor)
		{
			continue;
		}

		PollenGenerator->SetActorHiddenInGame(false);
		PollenGenerator->SetPollenCount(StageInfoDataAsset->PollenColorCount);
	}
}
