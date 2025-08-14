// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BeeSubMenuWidget.h"

void UBeeSubMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
}

FReply UBeeSubMenuWidget::NativeOnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	return Super::NativeOnKeyDown(MyGeometry, InKeyEvent);
}
