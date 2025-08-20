// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BeeExitCheckWidget.h"

#include "Components/Button.h"

void UBeeExitCheckWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ConfirmBtn->OnClicked.AddDynamic(this, &UBeeExitCheckWidget::OnConfirmButtonClicked);
	CancelBtn->OnClicked.AddDynamic(this, &UBeeExitCheckWidget::OnCancelButtonClicked);
}

void UBeeExitCheckWidget::OnConfirmButtonClicked()
{
	ConfirmButtonClickedEvent.Broadcast();
}

void UBeeExitCheckWidget::OnCancelButtonClicked()
{
	CancelButtonClickedEvent.Broadcast();
}

