// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BeePuzzleStageWidget.h"

#include "Game/BeeGameInstance.h"
#include "Game/BeePuzzleManageSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "UI/BeeStoryWidget.h"
#include "UI/BeeSubMenuWidget.h"

void UBeePuzzleStageWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OpenSubMenuBtn->OnClicked.AddDynamic(this, &UBeePuzzleStageWidget::OpenSubMenu);
	RestartBtn->OnClicked.AddDynamic(this, &UBeePuzzleStageWidget::RestartStage);
	UndoBtn->OnClicked.AddDynamic(this, &UBeePuzzleStageWidget::UndoLastAction);

	UndoBtn->SetIsEnabled(false);
	UndoBtn->SetColorAndOpacity(FLinearColor::Gray);

	UBeePuzzleManageSubsystem* PuzzleManageSubsystem = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UBeePuzzleManageSubsystem>();
	PuzzleManageSubsystem->OnColorMixed.AddDynamic(this, &UBeePuzzleStageWidget::OnColorMixed);
	PuzzleManageSubsystem->OnPuzzleFinished.AddDynamic(this, &UBeePuzzleStageWidget::OnPuzzleFinished);
	
	StoryWidget->SetVisibility(ESlateVisibility::Hidden);
	SubMenuWidget->SetVisibility(ESlateVisibility::Hidden);
}

void UBeePuzzleStageWidget::OpenSubMenu()
{
	SubMenuWidget->SetVisibility(ESlateVisibility::Visible);
}

void UBeePuzzleStageWidget::RestartStage()
{
	UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UBeePuzzleManageSubsystem>()->ClearData();
	FString LevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelName), true);
}

void UBeePuzzleStageWidget::UndoLastAction()
{
	//TODO: Undo 구현
	bool bIsCanUndo = false;
	if (UBeePuzzleManageSubsystem* PuzzleManageSubsystem = UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<UBeePuzzleManageSubsystem>())
	{
		bIsCanUndo = PuzzleManageSubsystem->UndoBuildingMaterialColorMixAction();
	}
	
	if (!bIsCanUndo)
	{
		UndoBtn->SetIsEnabled(false);
		UndoBtn->SetColorAndOpacity(FLinearColor::Gray);
	}
}

void UBeePuzzleStageWidget::OnPuzzleFinished()
{
	StoryWidget->SetCurrentStoryType(GetWorld()->GetGameInstanceChecked<UBeeGameInstance>()->GetCurrentPlayingStageNumber(), true);
	StoryWidget->SetVisibility(ESlateVisibility::Visible);
}

void UBeePuzzleStageWidget::OnColorMixed()
{
	UndoBtn->SetIsEnabled(true);
	UndoBtn->SetColorAndOpacity(FLinearColor::White);
}
