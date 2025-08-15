// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BeePuzzleStageWidget.h"

#include "Kismet/GameplayStatics.h"
#include "UI/BeeSubMenuWidget.h"

void UBeePuzzleStageWidget::NativeConstruct()
{
	Super::NativeConstruct();

	OpenSubMenuBtn->OnClicked.AddDynamic(this, &UBeePuzzleStageWidget::OpenSubMenu);
	RestartBtn->OnClicked.AddDynamic(this, &UBeePuzzleStageWidget::RestartStage);
	UndoBtn->OnClicked.AddDynamic(this, &UBeePuzzleStageWidget::UndoLastAction);
}

void UBeePuzzleStageWidget::OpenSubMenu()
{
	SubMenuWidget->SetVisibility(ESlateVisibility::Visible);
}

void UBeePuzzleStageWidget::RestartStage()
{
	FString LevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelName), true);
}

void UBeePuzzleStageWidget::UndoLastAction()
{
	//TODO: Undo 구현
}
