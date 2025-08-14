#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EResolutionTypes : uint8
{
	HD,
	FWXGA,
	HDP,
	FHD,
	EnumEnd UMETA(Hidden)
};
ENUM_RANGE_BY_COUNT(EResolutionTypes, EResolutionTypes::EnumEnd);

USTRUCT(BlueprintType)
struct FResolutionValueHelper
{
	GENERATED_BODY()
	
	FResolutionValueHelper()
	{
		ResolutionValues.Emplace("1280", "720"); // HD
		ResolutionValues.Emplace("1366", "768"); // FWXGA
		ResolutionValues.Emplace("1600", "900"); // HDP
		ResolutionValues.Emplace("1920", "1080"); // FHD

		EnumPath = TEXT("/Script/Project_LLL.EResolutionTypes");
	}

	TArray<TTuple<FString, FString>> ResolutionValues;

	FString EnumPath;
};