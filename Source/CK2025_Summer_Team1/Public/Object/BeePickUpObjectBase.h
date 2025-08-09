// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Object/BeeSelectableActorBase.h"
#include "BeePickUpObjectBase.generated.h"

/**
 * 
 */
UCLASS()
class CK2025_SUMMER_TEAM1_API ABeePickUpObjectBase : public ABeeSelectableActorBase
{
	GENERATED_BODY()

public:
	ABeePickUpObjectBase();

public:
	virtual void BeginPlay() override;
	
protected:
	virtual void NotifyActorOnClicked(FKey ButtonPressed = EKeys::LeftMouseButton) override;
	virtual void NotifyActorOnReleased(FKey ButtonReleased = EKeys::LeftMouseButton) override;
};
