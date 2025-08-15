// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BeeSubMenuWidget.h"

#include "UI/BeeExitCheckWidget.h"
#include "UI/BeeSettingWidget.h"

void UBeeSubMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
}

FReply UBeeSubMenuWidget::NativeOnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	return Super::NativeOnKeyDown(MyGeometry, InKeyEvent);

	if (InKeyEvent.GetKey() == EKeys::Escape && IsVisible())
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
}

void UBeeSubMenuWidget::OnReturnBtnClicked()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UBeeSubMenuWidget::OnExitBtnClicked()
{
	ExitCheckWidget->SetVisibility(ESlateVisibility::Visible);
}

void UBeeSubMenuWidget::OnSettingBtnClicked()
{
	SettingWidget->SetVisibility(ESlateVisibility::Visible);
}
