// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Data/BeeStringDataTable.h"
#include "BeeStoryWidget.generated.h"

class UBeeStoryResourceDataAsset;
class UBeeExitCheckWidget;
class UImage;
class UTextBlock;
class UButton;
/**
 * 
 */
UCLASS()
class CK2025_SUMMER_TEAM1_API UBeeStoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void SetCurrentStoryType(int32 StageNumber, bool IsPuzzleStage = false);
	
protected:
	UFUNCTION(BlueprintCallable)
	void OnTextDisplayEventBtnClicked();

	UFUNCTION(BlueprintCallable)
	void OnFadeOutComplete();
	
protected:
	UFUNCTION(BlueprintCallable)
	void OnSkipButtonClicked();

	UFUNCTION(BlueprintCallable)
	void OnSkipButtonConfirmed();

	UFUNCTION(BlueprintCallable)
	void OnSkipButtonCanceled();

protected:
	UFUNCTION(BlueprintCallable)
	void SetNextSpeaker();
	
	UFUNCTION(BlueprintCallable)
	void DisplayDialogueTextSequence();

	UFUNCTION(BlueprintCallable)
	void DisplayDialogueTextImmediately();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> SkipBtn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> TextDisplayEventBtn;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UTextBlock> CharacterNameTextBlock;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UTextBlock> CharacterDialogueTextBlock;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UImage> CharacterNameBackgroundImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UImage> CharacterDialogueBackgroundImage;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UImage> PlayerCharacterImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UImage> OtherCharacterImage;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UImage> ClickHintImage;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UBeeExitCheckWidget> ExitCheckWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", DisplayName = "스토리 캐릭터 일러스트 데이터 에셋")
	TObjectPtr<const UBeeStoryResourceDataAsset> StoryResourceDataAsset;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", DisplayName = "스토리 텍스트 데이터 테이블")
	TObjectPtr<const UDataTable> DialogueTextDataTable;
	
	TArray<const FStringDataTable*> DialogueTextData;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", DisplayName = "텍스트 출력 딜레이")
	float DialogueTextDisplayTick;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", DisplayName = "플레이어 캐릭터 대화 배경 아웃라인 컬러")
	FLinearColor PlayerCharacterDialogueOutlineColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", DisplayName = "NPC 대화 배경 이미지 아웃라인 컬러")
	FLinearColor OtherCharacterDialogueOutlineColor;

protected:
	uint32 bIsIntroStory : 1;
	
	const FStringDataTable* CurrentDialogueText;
	
	int32 NextDialogueIndex;
	
	int32 CurrentWordsIndex;
	
	FTimerHandle DialogueTextDisplayingHandle;
};
