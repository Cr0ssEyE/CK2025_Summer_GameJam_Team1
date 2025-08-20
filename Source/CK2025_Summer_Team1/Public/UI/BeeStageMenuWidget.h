// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Constant/BeeAssetLocations.h"
#include "Kismet/GameplayStatics.h"
#include "BeeStageMenuWidget.generated.h"

class UBeeStoryWidget;
class UBeeExitCheckWidget;
class UBeeSubMenuWidget;
class UTextBlock;
class UImage;
class UButton;
/**
 * 
 */
UCLASS()
class CK2025_SUMMER_TEAM1_API UBeeStageMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	virtual FReply NativeOnKeyDown(const FGeometry& MyGeometry, const FKeyEvent& InKeyEvent) override;

	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;
	
public:
	UFUNCTION(BlueprintCallable)
	void PlayNewBuildingCreateAnimation(const int32 StageNumber);
	
protected:
	UFUNCTION(BlueprintCallable)
	void OpenSubMenuWidget();

	UFUNCTION(BlueprintCallable)
	void OnFadeInComplete();

	UFUNCTION(BlueprintCallable)
	void OnFadeOutComplete();

protected:
	UFUNCTION(BlueprintCallable)
	void OnStageEnterBtnClicked();
	
	UFUNCTION(BlueprintCallable)
	void OnStageOneBtnClicked();

	UFUNCTION(BlueprintCallable)
	void OnStageTwoBtnClicked();

	UFUNCTION(BlueprintCallable)
	void OnStageThreeBtnClicked();

	UFUNCTION(BlueprintCallable)
	void OnStageFourBtnClicked();

	UFUNCTION(BlueprintCallable)
	void OnStageFiveBtnClicked();

protected:
	UFUNCTION(BlueprintCallable)
	void EnterSelectedStage();
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE void EnterStageOne() { UGameplayStatics::OpenLevel(GetWorld(), LEVEL_NAME_STAGE_ONE); }

 	UFUNCTION(BlueprintCallable)
	FORCEINLINE void EnterStageTwo() { UGameplayStatics::OpenLevel(GetWorld(), LEVEL_NAME_STAGE_TWO); }
	
 	UFUNCTION(BlueprintCallable)
	FORCEINLINE void EnterStageThree() { UGameplayStatics::OpenLevel(GetWorld(), LEVEL_NAME_STAGE_THREE); }
	  	
 	UFUNCTION(BlueprintCallable)
	FORCEINLINE void EnterStageFour() { UGameplayStatics::OpenLevel(GetWorld(), LEVEL_NAME_STAGE_FOUR); }
	  	
 	UFUNCTION(BlueprintCallable)
 	FORCEINLINE void EnterStageFive() { UGameplayStatics::OpenLevel(GetWorld(), LEVEL_NAME_STAGE_FIVE); }
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> MenuBtn;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> StageEnterBtn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> StageOneBtn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UTextBlock> StageOneText;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> StageTwoBtn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UTextBlock> StageTwoText;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> StageThreeBtn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UTextBlock> StageThreeText;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> StageFourBtn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UTextBlock> StageFourText;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UButton> StageFiveBtn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UTextBlock> StageFiveText;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UImage> StageOneBuildingImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UImage> StageTwoBuildingImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UImage> StageThreeBuildingImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UImage> StageFourBuildingImage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UImage> StageFiveBuildingImage;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Transient, meta=(BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> StageOneBuildingCreateAnimation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Transient, meta=(BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> StageTwoBuildingCreateAnimation;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Transient, meta=(BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> StageThreeBuildingCreateAnimation;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Transient, meta=(BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> StageFourBuildingCreateAnimation;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Transient, meta=(BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> StageFiveBuildingCreateAnimation;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TObjectPtr<UTexture2D> DisabledStageTexture;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FLinearColor DisabledStageTextColor;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UBeeStoryWidget> StoryWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (BindWidget))
	TObjectPtr<UBeeSubMenuWidget> SubMenuWidget;

protected:
	uint32 SelectedStageNumber;
};
