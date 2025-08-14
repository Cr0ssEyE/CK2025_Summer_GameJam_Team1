// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BeeFadeManageWidget.h"
#include "Kismet/GameplayStatics.h"

void UBeeFadeManageWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void UBeeFadeManageWidget::BeginFadeIn()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->DisableInput(PlayerController);
	
	PlayAnimationForward(FadeInAnimation);
}

void UBeeFadeManageWidget::BeginFadeOut()
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->DisableInput(PlayerController);
	
	PlayAnimationForward(FadeOutAnimation);
}

void UBeeFadeManageWidget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	Super::OnAnimationFinished_Implementation(Animation);

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PlayerController->EnableInput(PlayerController);
	
	if (Animation == FadeInAnimation)
	{
		OnFadeInCompleteEvent.Broadcast();
		return;
	}
	
	if (Animation == FadeOutAnimation)
	{
		OnFadeOutCompleteEvent.Broadcast();
	}
}
