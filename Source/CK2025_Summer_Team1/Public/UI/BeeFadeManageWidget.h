// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BeeFadeManageWidget.generated.h"

class UImage;

/**
 * 
 */
UCLASS()
class CK2025_SUMMER_TEAM1_API UBeeFadeManageWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual void BeginFadeIn();
	
	virtual void BeginFadeOut();
	
protected:
	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UImage> FadeImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Transient, meta=(BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> FadeInAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Transient, meta=(BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> FadeOutAnimation;
	
};
