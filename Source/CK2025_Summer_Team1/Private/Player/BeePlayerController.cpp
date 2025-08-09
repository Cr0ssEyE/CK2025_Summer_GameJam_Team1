// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BeePlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Constant/BeeAssetLocations.h"
#include "Constant/BeeCollisionNames.h"
#include "Data/BeePlayerDataAsset.h"
#include "Util/BeeConstructorHelper.h"

ABeePlayerController::ABeePlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	DefaultMouseCursor = EMouseCursor::Default;

	if (UBeePlayerDataAsset* PlayerDataAsset = FBeeConstructorHelper::FindAndGetObject<UBeePlayerDataAsset>(LOCATION_PLAYER_DATA))
	{
		DefaultMappingContext = PlayerDataAsset->PlayerInputMappingContext;
		MouseHoldAction = PlayerDataAsset->PlayerMouseHoldAction;
		MouseClickAction = PlayerDataAsset->PlayerMouseClickAction;
		ObjectPickUpHeight = PlayerDataAsset->ObjectPickUpHeight;
		ObjectSnapRange = PlayerDataAsset->ObjectSnapRange;
	}

	bIsObjectPickup = false;
}

void ABeePlayerController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABeePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(MouseHoldAction, ETriggerEvent::Started, this, &ABeePlayerController::SelectHoldStarted);
		EnhancedInputComponent->BindAction(MouseHoldAction, ETriggerEvent::Completed, this, &ABeePlayerController::SelectHoldCompleted);
		EnhancedInputComponent->BindAction(MouseHoldAction, ETriggerEvent::Canceled, this, &ABeePlayerController::SelectHoldCompleted);
		
		EnhancedInputComponent->BindAction(MouseClickAction, ETriggerEvent::Started, this, &ABeePlayerController::SelectClickStarted);
		EnhancedInputComponent->BindAction(MouseClickAction, ETriggerEvent::Completed, this, &ABeePlayerController::SelectClickCompleted);
		EnhancedInputComponent->BindAction(MouseClickAction, ETriggerEvent::Canceled, this, &ABeePlayerController::SelectClickCompleted);
	}
}

void ABeePlayerController::SelectHoldStarted(const FInputActionValue& InputActionValue)
{
	
}

void ABeePlayerController::SelectHoldCompleted(const FInputActionValue& InputActionValue)
{
	if (PickUpObject.IsValid())
	{
		bIsObjectPickup = false;
		PickUpObject->SetActorLocation(PickUpObject->GetActorLocation() - FVector(0.f, 0.f, ObjectPickUpHeight / 2));
		PickUpObject.Reset();
	}
}

void ABeePlayerController::SelectClickStarted(const FInputActionValue& InputActionValue)
{
	if (bIsObjectPickup)
	{
		return;
	}
	
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_TRACE_PUZZLE_OBJECT, false, Hit);
	
	if (AActor* PuzzleActor = Hit.GetActor())
	{
		PickUpObject = PuzzleActor;
		UE_LOG(LogTemp, Log, TEXT("Clicked on: %s"), *Hit.GetActor()->GetName());
		bIsObjectPickup = true;
		GetWorldTimerManager().SetTimerForNextTick(this, &ABeePlayerController::PickupObjectMoveToMouseCursor);
	}
}

void ABeePlayerController::SelectClickCompleted(const FInputActionValue& InputActionValue)
{
	
}

void ABeePlayerController::PickupObjectMoveToMouseCursor()
{
	if (PickUpObject.IsValid() && bIsObjectPickup)
	{
		FHitResult Hit;
		if (GetHitResultUnderCursor(ECC_TRACE_PLACE_OBJECT, false, Hit))
		{
			FVector TargetLocation = Hit.ImpactPoint;
			PickUpObject->SetActorLocation(TargetLocation + FVector(0.f, 0.f, ObjectPickUpHeight));
		}
		GetWorldTimerManager().SetTimerForNextTick(this, &ABeePlayerController::PickupObjectMoveToMouseCursor);
	}
}
