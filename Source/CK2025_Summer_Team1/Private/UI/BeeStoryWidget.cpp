// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BeeStoryWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Constant/BeeAssetLocations.h"
#include "Data/BeeStoryResourceDataAsset.h"
#include "Game/BeeGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "UI/BeeExitCheckWidget.h"
#include "Util/BeeSaveGameData.h"

void UBeeStoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	GetWorld()->GetGameInstanceChecked<UBeeGameInstance>()->FadeWidgetFadeOutCompleteEvent.AddDynamic(this, &UBeeStoryWidget::OnFadeOutComplete);
	SkipBtn->OnClicked.AddDynamic(this, &UBeeStoryWidget::OnSkipButtonClicked);
	ExitCheckWidget->ConfirmButtonClickedEvent.AddDynamic(this, &UBeeStoryWidget::OnSkipButtonConfirmed);
	ExitCheckWidget->CancelButtonClickedEvent.AddDynamic(this, &UBeeStoryWidget::OnSkipButtonCanceled);
	TextDisplayEventBtn->OnClicked.AddDynamic(this, &UBeeStoryWidget::OnTextDisplayEventBtnClicked);

	ExitCheckWidget->SetVisibility(ESlateVisibility::Hidden);
	ClickHintImage->SetVisibility(ESlateVisibility::Hidden);
	bIsIntroStory = false;
}

void UBeeStoryWidget::SetCurrentStoryType(int32 StageNumber, bool IsPuzzleStage)
{
	bIsIntroStory = UGameplayStatics::GetCurrentLevelName(GetWorld()) == LEVEL_NAME_STAGE_MENU;
	const int32 CurrentStageNumber = StageNumber;
	
	TArray<FStringDataTable*> LoadedStringDataArray;
	DialogueTextDataTable->GetAllRows<FStringDataTable>(TEXT("Failed To Load Reward Data Tables"), LoadedStringDataArray);
	
	for (const FStringDataTable* LoadedStringData : LoadedStringDataArray)
	{
		if (LoadedStringData->StageNumber != CurrentStageNumber)
		{
			continue;
		}

		if ((!LoadedStringData->IsClearStory && IsPuzzleStage) || (LoadedStringData->IsClearStory && !IsPuzzleStage))
		{
			continue;
		}
		
		DialogueTextData.Add(LoadedStringData);
	}

	OtherCharacterImage->SetBrushFromTexture(StoryResourceDataAsset->StageCharactersTextures[StageNumber - 1]);
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
	// = 퍼즐 스테이지
	if (UGameplayStatics::GetCurrentLevelName(GetWorld()) != LEVEL_NAME_STAGE_MENU)
	{
		UBeeGameInstance * GameInstance = GetWorld()->GetGameInstanceChecked<UBeeGameInstance>();
		UBeeSaveGameData* SaveGameData = GameInstance->GetCurrentSaveGameData();
		SaveGameData->LastClearedStageNumber = GameInstance->GetCurrentPlayingStageNumber();
		if (SaveGameData->MaxClearedStageNumber < GameInstance->GetCurrentPlayingStageNumber())
		{
			SaveGameData->MaxClearedStageNumber = GameInstance->GetCurrentPlayingStageNumber();
			GameInstance->SaveCurrentSaveGameData();
		}
		
		UGameplayStatics::OpenLevel(GetWorld(), LEVEL_NAME_STAGE_MENU);
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
	switch (CurrentDialogueText->SpeakerType)
	{
	case ESpeakerTypes::Player:
		CharacterDialogueBackgroundImage->SetColorAndOpacity(PlayerCharacterDialogueOutlineColor);
		PlayerCharacterImage->SetColorAndOpacity(FLinearColor::White);
		OtherCharacterImage->SetColorAndOpacity(FLinearColor(0.15f , 0.15f, 0.15f, 1.f));
		break;
	case ESpeakerTypes::NPC:
		CharacterDialogueBackgroundImage->SetColorAndOpacity(OtherCharacterDialogueOutlineColor);
		PlayerCharacterImage->SetColorAndOpacity(FLinearColor(0.15f , 0.15f, 0.15f, 1.f));
		OtherCharacterImage->SetColorAndOpacity(FLinearColor::White);
		break;
	case ESpeakerTypes::Other:
		CharacterDialogueBackgroundImage->SetColorAndOpacity(FLinearColor::Gray);
		PlayerCharacterImage->SetColorAndOpacity(FLinearColor(0.15f , 0.15f, 0.15f, 1.f));
		OtherCharacterImage->SetColorAndOpacity(FLinearColor(0.15f , 0.15f, 0.15f, 1.f));
		break;
	default:
		checkNoEntry();
		break;
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
		DisplayDialogueTextImmediately();
	}
}

void UBeeStoryWidget::DisplayDialogueTextImmediately()
{
	GetWorld()->GetTimerManager().ClearTimer(DialogueTextDisplayingHandle);
	NextDialogueIndex++;
	CharacterDialogueTextBlock->SetText(FText::FromString(CurrentDialogueText->Words));
	ClickHintImage->SetVisibility(ESlateVisibility::Visible);
}
