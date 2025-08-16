// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BeeFadeManageWidget.h"

#include "Game/BeeGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UBeeFadeManageWidget::NativeConstruct()
{
	Super::NativeConstruct();

	
}

void UBeeFadeManageWidget::BeginFadeIn()
{
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		PlayerController->DisableInput(PlayerController);
	}

	SetVisibility(ESlateVisibility::Visible);
	PlayAnimationForward(FadeInAnimation);
}

void UBeeFadeManageWidget::BeginFadeOut()
{
	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		PlayerController->DisableInput(PlayerController);
	}

	SetVisibility(ESlateVisibility::Visible);
	PlayAnimationForward(FadeOutAnimation);
}

void UBeeFadeManageWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	Super::OnAnimationFinished_Implementation(Animation);

	if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		PlayerController->EnableInput(PlayerController);
	}
	
	UBeeGameInstance* GameInstance = GetWorld()->GetGameInstance<UBeeGameInstance>();
	
	if (Animation == FadeInAnimation)
	{
		GameInstance->FadeWidgetFadeInCompleteEvent.Broadcast();
		GameInstance->OnFadeComplete();
		SetVisibility(ESlateVisibility::Hidden);
	}
	else if (Animation == FadeOutAnimation)
	{
		GameInstance->FadeWidgetFadeOutCompleteEvent.Broadcast();
		GameInstance->OnFadeComplete();
	}
}
