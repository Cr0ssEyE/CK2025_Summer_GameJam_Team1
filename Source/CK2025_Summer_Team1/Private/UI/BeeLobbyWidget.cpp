// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BeeLobbyWidget.h"

#include "Components/Button.h"
#include "Constant/BeeAssetLocations.h"
#include "Game/BeeGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "UI/BeeExitCheckWidget.h"
#include "Util/BeeSaveGameData.h"

void UBeeLobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UBeeGameInstance* GameInstance = GetWorld()->GetGameInstanceChecked<UBeeGameInstance>();
	GameInstance->FadeWidgetFadeInCompleteEvent.AddDynamic(this, &UBeeLobbyWidget::OnFadeInComplete);
	GameInstance->FadeWidgetFadeOutCompleteEvent.AddDynamic(this, &UBeeLobbyWidget::LoadStageMenuLevel);
	
	StartButton->OnClicked.AddDynamic(this, &UBeeLobbyWidget::OnStartButtonClicked);
	StartButton->SetVisibility(ESlateVisibility::Hidden);
	StartButton->SetIsEnabled(false);

	ExitButton->OnClicked.AddDynamic(this, &UBeeLobbyWidget::OnExitButtonClicked);
	ExitButton->SetVisibility(ESlateVisibility::Hidden);
	ExitButton->SetIsEnabled(false);
	
	ExitCheckWidget->ConfirmButtonClickedEvent.AddDynamic(this, &UBeeLobbyWidget::ExitGame);
	ExitCheckWidget->CancelButtonClickedEvent.AddDynamic(this, &UBeeLobbyWidget::CloseExitCheckWidget);
	ExitCheckWidget->SetVisibility(ESlateVisibility::Hidden);
	ExitCheckWidget->SetIsEnabled(false);
}

void UBeeLobbyWidget::OnFadeInComplete()
{
	StartButton->SetIsEnabled(true);
	StartButton->SetVisibility(ESlateVisibility::Visible);
	ExitButton->SetIsEnabled(true);
	ExitButton->SetVisibility(ESlateVisibility::Visible);
}

void UBeeLobbyWidget::OnStartButtonClicked()
{
	GetWorld()->GetGameInstanceChecked<UBeeGameInstance>()->FadeOut();
}

void UBeeLobbyWidget::OnExitButtonClicked()
{
	ExitCheckWidget->SetVisibility(ESlateVisibility::Visible);
	ExitCheckWidget->SetIsEnabled(true);
}

void UBeeLobbyWidget::LoadStageMenuLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), LEVEL_NAME_STAGE_MENU);
}

void UBeeLobbyWidget::CloseExitCheckWidget()
{
	ExitCheckWidget->SetVisibility(ESlateVisibility::Hidden);
	ExitCheckWidget->SetIsEnabled(false);
}

void UBeeLobbyWidget::ExitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}
