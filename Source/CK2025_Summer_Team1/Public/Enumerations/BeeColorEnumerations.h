#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EBuildingMaterialBaseColor : uint8
{
	None,
	BaseFirstColor,
	BaseSecondColor,
	BaseThirdColor,
	White = 50,
	Black,
	NotMixable = 100 UMETA(Hidden),
	MixFirstAndSecondColor,
	MixFirstAndThirdColor,
	MixSecondAndThirdColor,
	MixFirstAndWhiteColor,
	MixSecondAndWhiteColor,
	MixThirdAndWhiteColor,
	MixFirstAndBlackColor,
	MixSecondAndBlackColor,
	MixThirdAndBlackColor,
	Count UMETA(Hidden)
};

class CK2025_SUMMER_TEAM1_API FBeeColorEnumHelper
{
public:
	static bool FindMixedColor(EBuildingMaterialBaseColor DroppedColor, EBuildingMaterialBaseColor TargetColor, EBuildingMaterialBaseColor& MixedColor)
	{
		if (DroppedColor == TargetColor || DroppedColor == EBuildingMaterialBaseColor::None)
		{
			return false;
		}

		if (TargetColor == EBuildingMaterialBaseColor::None)
		{
			MixedColor = DroppedColor;
			return true;
		}

		int32 MixedValue = static_cast<int32>(DroppedColor) + static_cast<int32>(TargetColor);
		if (MixedValue >= static_cast<int32>(EBuildingMaterialBaseColor::NotMixable))
		{
			return false;
		}
		switch (DroppedColor)
		{
		case EBuildingMaterialBaseColor::BaseFirstColor:
			MixedColor = MixFirstColor(TargetColor);
			break;
		case EBuildingMaterialBaseColor::BaseSecondColor:
			MixedColor = MixSecondColor(TargetColor);
			break;
		case EBuildingMaterialBaseColor::BaseThirdColor:
			MixedColor = MixThirdColor(TargetColor);
			break;
		case EBuildingMaterialBaseColor::White:
			MixedColor = MixWhiteColor(TargetColor);
			break;
		case EBuildingMaterialBaseColor::Black:
			MixedColor = MixBlackColor(TargetColor);
			break;
		default:
			checkNoEntry();
			break;
		}
		return true;
	}

	static EBuildingMaterialBaseColor MixFirstColor(EBuildingMaterialBaseColor TargetColor)
	{
		switch (TargetColor)
		{
		case EBuildingMaterialBaseColor::BaseSecondColor:
			return EBuildingMaterialBaseColor::MixFirstAndSecondColor;
			break;
		case EBuildingMaterialBaseColor::BaseThirdColor:
			return EBuildingMaterialBaseColor::MixFirstAndThirdColor;
			break;
		case EBuildingMaterialBaseColor::White:
			return  EBuildingMaterialBaseColor::MixFirstAndWhiteColor;
			break;
		case EBuildingMaterialBaseColor::Black:
			return  EBuildingMaterialBaseColor::MixFirstAndBlackColor;
			break;
		default:
			checkNoEntry();
			break;
		}
		return EBuildingMaterialBaseColor::Black;
	}

	static EBuildingMaterialBaseColor MixSecondColor(EBuildingMaterialBaseColor TargetColor)
	{
		switch (TargetColor)
		{
		case EBuildingMaterialBaseColor::BaseFirstColor:
			return EBuildingMaterialBaseColor::MixFirstAndSecondColor;
		case EBuildingMaterialBaseColor::BaseThirdColor:
			return EBuildingMaterialBaseColor::MixSecondAndThirdColor;
		case EBuildingMaterialBaseColor::White:
			return EBuildingMaterialBaseColor::MixSecondAndWhiteColor;
		case EBuildingMaterialBaseColor::Black:
			return EBuildingMaterialBaseColor::MixSecondAndBlackColor;
		default:
			checkNoEntry();
			break;
		}
		return EBuildingMaterialBaseColor::Black;
	}

	static EBuildingMaterialBaseColor MixThirdColor(EBuildingMaterialBaseColor TargetColor)
	{
		switch (TargetColor)
		{
		case EBuildingMaterialBaseColor::BaseFirstColor:
			return EBuildingMaterialBaseColor::MixFirstAndThirdColor;
		case EBuildingMaterialBaseColor::BaseSecondColor:
			return EBuildingMaterialBaseColor::MixSecondAndThirdColor;
		case EBuildingMaterialBaseColor::White:
			return EBuildingMaterialBaseColor::MixThirdAndWhiteColor;
		case EBuildingMaterialBaseColor::Black:
			return EBuildingMaterialBaseColor::MixThirdAndBlackColor;
		default:
			checkNoEntry();
			break;
		}
		return EBuildingMaterialBaseColor::Black;
	}

	static EBuildingMaterialBaseColor MixWhiteColor(EBuildingMaterialBaseColor TargetColor)
	{
		switch (TargetColor)
		{
		case EBuildingMaterialBaseColor::BaseFirstColor:
			return EBuildingMaterialBaseColor::MixFirstAndWhiteColor;
		case EBuildingMaterialBaseColor::BaseSecondColor:
			return EBuildingMaterialBaseColor::MixSecondAndWhiteColor;
		case EBuildingMaterialBaseColor::BaseThirdColor:
			return EBuildingMaterialBaseColor::MixThirdAndWhiteColor;
		default:
			checkNoEntry();
			break;
		}
		return EBuildingMaterialBaseColor::Black;
	}

	static EBuildingMaterialBaseColor MixBlackColor(EBuildingMaterialBaseColor TargetColor)
	{
		switch (TargetColor)
		{
		case EBuildingMaterialBaseColor::BaseFirstColor:
			return EBuildingMaterialBaseColor::MixFirstAndBlackColor;
		case EBuildingMaterialBaseColor::BaseSecondColor:
			return EBuildingMaterialBaseColor::MixSecondAndBlackColor;
		case EBuildingMaterialBaseColor::BaseThirdColor:
			return EBuildingMaterialBaseColor::MixThirdAndBlackColor;
		default:
			checkNoEntry();
			break;
		}
		return EBuildingMaterialBaseColor::Black;
	}
};
