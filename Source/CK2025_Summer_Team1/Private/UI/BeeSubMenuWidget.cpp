// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BeeSubMenuWidget.h"

#include "Constant/BeeAssetLocations.h"
#include "Kismet/GameplayStatics.h"
#include "UI/BeeExitCheckWidget.h"
#include "UI/BeeSettingWidget.h"

void UBeeSubMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ReturnBtn->OnClicked.AddDynamic(this, &UBeeSubMenuWidget::OnReturnBtnClicked);
	SettingBtn->OnClicked.AddDynamic(this, &UBeeSubMenuWidget::OnSettingBtnClicked);
	ExitBtn->OnClicked.AddDynamic(this, &UBeeSubMenuWidget::OnExitBtnClicked);

	ExitCheckWidget->ConfirmButtonClickedEvent.AddDynamic(this, &UBeeSubMenuWidget::OnExitCheckConfirmed);
	ExitCheckWidget->CancelButtonClickedEvent.AddDynamic(this, &UBeeSubMenuWidget::OnExitCheckCanceled);
	
	SetVisibility(ESlateVisibility::Hidden);
	SettingWidget->SetVisibility(ESlateVisibility::Hidden);
	ExitCheckWidget->SetVisibility(ESlateVisibility::Hidden);
}

FReply UBeeSubMenuWidget::NativeOnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	return Super::NativeOnKeyDown(MyGeometry, InKeyEvent);
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

void UBeeSubMenuWidget::OnExitCheckConfirmed()
{
	if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == LEVEL_NAME_STAGE_MENU)
	{
		UGameplayStatics::OpenLevel(GetWorld(), LEVEL_NAME_LOBBY);
		return;
	}

	UGameplayStatics::OpenLevel(GetWorld(), LEVEL_NAME_STAGE_MENU);
}

void UBeeSubMenuWidget::OnExitCheckCanceled()
{
	ExitCheckWidget->SetVisibility(ESlateVisibility::Hidden);
}
