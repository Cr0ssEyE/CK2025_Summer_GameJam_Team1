// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BeeSelectableObjectDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class CK2025_SUMMER_TEAM1_API UBeeSelectableObjectDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = "Mesh", DisplayName = "스태틱 메시")
	TObjectPtr<UStaticMesh> ObjectMesh;
};
