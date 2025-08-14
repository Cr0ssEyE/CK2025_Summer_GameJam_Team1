// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BeeStageMenuWidget.h"

#include "Components/Button.h"
#include "Game/BeeGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "UI/BeeSubMenuWidget.h"
#include "Util/BeeSaveGameData.h"

void UBeeStageMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MenuBtn->OnClicked.AddDynamic(this, &UBeeStageMenuWidget::OpenMenuPopUpWidget);
	StageEnterBtn->OnClicked.AddDynamic(this, &UBeeStageMenuWidget::OnStageEnterBtnClicked);
	StageOneBtn->OnClicked.AddDynamic(this, &UBeeStageMenuWidget::OnStageOneBtnClicked);
	StageTwoBtn->OnClicked.AddDynamic(this, &UBeeStageMenuWidget::OnStageTwoBtnClicked);
	StageThreeBtn->OnClicked.AddDynamic(this, &UBeeStageMenuWidget::OnStageThreeBtnClicked);
	StageFourBtn->OnClicked.AddDynamic(this, &UBeeStageMenuWidget::OnStageFourBtnClicked);
	StageFiveBtn->OnClicked.AddDynamic(this, &UBeeStageMenuWidget::OnStageFiveBtnClicked);

	StageEnterBtn->SetVisibility(ESlateVisibility::Hidden);

	GetWorld()->GetGameInstanceChecked<UBeeGameInstance>()->GetOnFadeInCompleteDelegate()->AddDynamic(this, &UBeeStageMenuWidget::OnFadeInComplete);
}

FReply UBeeStageMenuWidget::NativeOnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent)
{
	FReply Reply = Super::NativeOnKeyDown(MyGeometry, InKeyEvent);

	if (InKeyEvent.GetKey() == EKeys::Escape)
	{
		if (BeeMenuPopUpWidget->IsVisible())
		{
			BeeMenuPopUpWidget->SetVisibility(ESlateVisibility::Hidden);
			return FReply::Handled();
		}
		
		OpenMenuPopUpWidget();
		return FReply::Handled();
	}

	return Reply;
}

void UBeeStageMenuWidget::PlayNewBuildingCreateAnimation(const int32 StageNumber)
{
	switch (StageNumber)
	{
		case 1:
			PlayAnimationForward(StageOneBuildingCreateAnimation);
			break;
		case 2:
			PlayAnimationForward(StageTwoBuildingCreateAnimation);
			break;
		case 3:
			PlayAnimationForward(StageThreeBuildingCreateAnimation);
			break;
		case 4:
			PlayAnimationForward(StageFourBuildingCreateAnimation);
			break;
		case 5:
			PlayAnimationForward(StageFiveBuildingCreateAnimation);
			break;
	default:
		checkNoEntry();
	}

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->DisableInput(PlayerController);
}

void UBeeStageMenuWidget::OpenMenuPopUpWidget()
{
	if (!BeeMenuPopUpWidget->IsVisible())
	{
		BeeMenuPopUpWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void UBeeStageMenuWidget::OnFadeInComplete()
{
	UBeeSaveGameData* CurrentData = GetWorld()->GetGameInstanceChecked<UBeeGameInstance>()->GetCurrentSaveGameData();
	int32 LastClearedStageNumber = GetWorld()->GetGameInstanceChecked<UBeeGameInstance>()->GetLastClearedStageNumber();
	if (CurrentData->MaxClearedStageNumber < LastClearedStageNumber)
	{
		CurrentData->MaxClearedStageNumber = LastClearedStageNumber;
		GetWorld()->GetGameInstanceChecked<UBeeGameInstance>()->SaveCurrentSaveGameData();

		PlayNewBuildingCreateAnimation(LastClearedStageNumber);
	}
}

void UBeeStageMenuWidget::OnFadeOutComplete()
{
	
}

void UBeeStageMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	Super::OnAnimationFinished_Implementation(Animation);

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->EnableInput(PlayerController);
}

void UBeeStageMenuWidget::OnStageEnterBtnClicked()
{
	GetWorld()->GetGameInstanceChecked<UBeeGameInstance>()->GetOnFadeOutCompleteDelegate()->AddDynamic(this, &UBeeStageMenuWidget::EnterSelectedStage);
	GetWorld()->GetGameInstanceChecked<UBeeGameInstance>()->FadeOut();
}

void UBeeStageMenuWidget::OnStageOneBtnClicked()
{
	SelectedStageNumber = 1;
	StageEnterBtn->SetVisibility(ESlateVisibility::Visible);
	FWidgetTransform BaseTransform = StageOneBtn->GetRenderTransform();
	BaseTransform.Translation += FVector2D(0.0f, 100.0f);
	StageEnterBtn->SetRenderTransform(BaseTransform);
}

void UBeeStageMenuWidget::OnStageTwoBtnClicked()
{
	SelectedStageNumber = 2;
	StageEnterBtn->SetVisibility(ESlateVisibility::Visible);
	FWidgetTransform BaseTransform = StageTwoBtn->GetRenderTransform();
	BaseTransform.Translation += FVector2D(0.0f, 100.0f);
	StageEnterBtn->SetRenderTransform(BaseTransform);
}

void UBeeStageMenuWidget::OnStageThreeBtnClicked()
{
	SelectedStageNumber = 3;
	StageEnterBtn->SetVisibility(ESlateVisibility::Visible);
	FWidgetTransform BaseTransform = StageThreeBtn->GetRenderTransform();
	BaseTransform.Translation += FVector2D(0.0f, 100.0f);
	StageEnterBtn->SetRenderTransform(BaseTransform);
}

void UBeeStageMenuWidget::OnStageFourBtnClicked()
{
	SelectedStageNumber = 4;
	StageEnterBtn->SetVisibility(ESlateVisibility::Visible);
	FWidgetTransform BaseTransform = StageFourBtn->GetRenderTransform();
	BaseTransform.Translation += FVector2D(0.0f, 100.0f);
	StageEnterBtn->SetRenderTransform(BaseTransform);
}

void UBeeStageMenuWidget::OnStageFiveBtnClicked()
{
	SelectedStageNumber = 5;
	StageEnterBtn->SetVisibility(ESlateVisibility::Visible);
	FWidgetTransform BaseTransform = StageFiveBtn->GetRenderTransform();
	BaseTransform.Translation += FVector2D(0.0f, 100.0f);
	StageEnterBtn->SetRenderTransform(BaseTransform);
}

void UBeeStageMenuWidget::EnterSelectedStage()
{
	switch (SelectedStageNumber)
	{
		case 1:
			EnterStageOne();
			break;
		case 2:
			EnterStageTwo();
			break;
		case 3:
			EnterStageThree();
			break;
		case 4:
			EnterStageFour();
			break;
		case 5:
			EnterStageFive();
			break;
		default:
			checkNoEntry();
			break;
	}
}
