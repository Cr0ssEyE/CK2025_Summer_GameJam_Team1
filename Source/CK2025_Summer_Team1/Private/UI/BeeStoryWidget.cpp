// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BeeStoryWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Constant/BeeAssetLocations.h"
#include "Game/BeeGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "UI/BeeExitCheckWidget.h"

void UBeeStoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	GetWorld()->GetGameInstanceChecked<UBeeGameInstance>()->FadeWidgetFadeOutCompleteEvent.AddDynamic(this, &UBeeStoryWidget::OnFadeOutComplete);
	SkipBtn->OnClicked.AddDynamic(this, &UBeeStoryWidget::OnSkipButtonClicked);
	ExitCheckWidget->GetConfirmButtonClickedEvent().AddDynamic(this, &UBeeStoryWidget::OnSkipButtonConfirmed);
	ExitCheckWidget->GetCancelButtonClickedEvent().AddDynamic(this, &UBeeStoryWidget::OnSkipButtonCanceled);
	TextDisplayEventBtn->OnClicked.AddDynamic(this, &UBeeStoryWidget::OnTextDisplayEventBtnClicked);

	ClickHintImage->SetVisibility(ESlateVisibility::Hidden);
	bIsIntroStory = false;
}

void UBeeStoryWidget::SetCurrentStoryType(int32 StageNumber)
{
	bIsIntroStory = UGameplayStatics::GetCurrentLevelName(GetWorld()) == LEVEL_NAME_LOBBY;
	const int32 CurrentStageNumber = StageNumber;
	
	TArray<FStringDataTable*> LoadedStringDataArray;
	DialogueTextDataTable->GetAllRows<FStringDataTable>(TEXT("Failed To Load Reward Data Tables"), LoadedStringDataArray);
	
	for (const FStringDataTable* LoadedStringData : LoadedStringDataArray)
	{
		if (LoadedStringData->StageNumber != CurrentStageNumber)
		{
			continue;
		}

		if (LoadedStringData->IsClearStory && bIsIntroStory)
		{
			return;
		}
		
		DialogueTextData.Add(LoadedStringData);
	}

	SetNextSpeaker();
}

void UBeeStoryWidget::OnTextDisplayEventBtnClicked()
{
	FTimerManager& TimerManager = GetWorld()->GetTimerManager();
	if (TimerManager.IsTimerActive(DialogueTextDisplayingHandle))
	{
		DisplayDialogueTextImmediately();
	}
	else
	{
		SetNextSpeaker();
	}
}

void UBeeStoryWidget::OnFadeOutComplete()
{
	GetWorld()->GetTimerManager().ClearTimer(DialogueTextDisplayingHandle);
	if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == LEVEL_NAME_LOBBY)
	{
		UGameplayStatics::OpenLevel(GetWorld(), LEVEL_NAME_LOBBY);
	}
}

void UBeeStoryWidget::OnSkipButtonClicked()
{
	ExitCheckWidget->SetVisibility(ESlateVisibility::Visible);
}

void UBeeStoryWidget::OnSkipButtonConfirmed()
{
	UBeeGameInstance* GameInstance = GetWorld()->GetGameInstanceChecked<UBeeGameInstance>();
	GameInstance->SaveCurrentSaveGameData();
	GameInstance->FadeOut();
}

void UBeeStoryWidget::OnSkipButtonCanceled()
{
	ExitCheckWidget->SetVisibility(ESlateVisibility::Hidden);
}

void UBeeStoryWidget::SetNextSpeaker()
{
	//TODO: 테이블 기반으로 다음 화자 UI 및 텍스트 출력
	if (DialogueTextData.Num() <= 0)
	{
		return;
	}

	if (NextDialogueIndex >= DialogueTextData.Num() - 1)
	{
		OnSkipButtonConfirmed();
		return;
	}
	
	ClickHintImage->SetVisibility(ESlateVisibility::Hidden);
	CurrentDialogueText = DialogueTextData[NextDialogueIndex];
	CharacterNameTextBlock->SetText(FText::FromString(CurrentDialogueText->Speaker));
	CharacterDialogueTextBlock->SetText(FText::FromString(""));
	CurrentWordsIndex = 0;
	
	//TODO: 화자에 따라 캐랙터 배경 및 색상 변경
	if (CurrentDialogueText->IsPlayer)
	{
		CharacterDialogueBackgroundImage->SetColorAndOpacity(PlayerCharacterDialogueOutlineColor);
		PlayerCharacterImage->SetColorAndOpacity(FLinearColor::White);
		OtherCharacterImage->SetColorAndOpacity(FLinearColor::Gray);
	}
	else
	{
		CharacterDialogueBackgroundImage->SetColorAndOpacity(OtherCharacterDialogueOutlineColor);
		PlayerCharacterImage->SetColorAndOpacity(FLinearColor::Gray);
		OtherCharacterImage->SetColorAndOpacity(FLinearColor::White);
	}
	
	GetWorld()->GetTimerManager().SetTimer(DialogueTextDisplayingHandle, this, &UBeeStoryWidget::DisplayDialogueTextSequence, DialogueTextDisplayTick, true);
}

void UBeeStoryWidget::DisplayDialogueTextSequence()
{
	const FString CurrentDialogueTextString = CharacterDialogueTextBlock->GetText().ToString() + CurrentDialogueText->Words[CurrentWordsIndex];
	CharacterDialogueTextBlock->SetText(FText::FromString(CurrentDialogueTextString));
	CurrentWordsIndex++;

	if (CurrentDialogueTextString.Equals(CurrentDialogueText->Words))
	{
		GetWorld()->GetTimerManager().ClearTimer(DialogueTextDisplayingHandle);
		ClickHintImage->SetVisibility(ESlateVisibility::Visible);
	}
}

void UBeeStoryWidget::DisplayDialogueTextImmediately()
{
	 GetWorld()->GetTimerManager().ClearTimer(DialogueTextDisplayingHandle);
	ClickHintImage->SetVisibility(ESlateVisibility::Visible);
}
