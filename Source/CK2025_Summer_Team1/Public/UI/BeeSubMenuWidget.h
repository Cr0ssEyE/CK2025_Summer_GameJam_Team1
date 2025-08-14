// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BeeSubMenuWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSubMenuClosedEvent);

/**
 * 
 */
UCLASS()
class CK2025_SUMMER_TEAM1_API UBeeSubMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
	virtual FReply NativeOnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;

public:
	FOnSubMenuClosedEvent OnSubMenuClosedEvent;
	
protected:

protected:
	
};
