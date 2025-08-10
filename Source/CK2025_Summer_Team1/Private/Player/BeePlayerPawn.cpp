// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BeePlayerPawn.h"

#include "Camera/CameraComponent.h"
#include "Constant/BeeAssetLocations.h"
#include "Data/BeePlayerDataAsset.h"
#include "GameFramework/SpringArmComponent.h"
#include "Util/BeeConstructorHelper.h"

// Sets default values
ABeePlayerPawn::ABeePlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// create the root
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	// create the camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->SetupAttachment(RootComponent);

	if (const UBeePlayerDataAsset* PlayerDataAsset = FBeeConstructorHelper::FindAndGetObject<UBeePlayerDataAsset>(LOCATION_PLAYER_DATA))
	{
		CameraArm->TargetArmLength = PlayerDataAsset->PlayerCameraDistance;
		CameraArm->TargetOffset = FVector(0.f, 0.f, PlayerDataAsset->PlayerCameraDistance);
		Camera->SetRelativeRotation(PlayerDataAsset->PlayerCameraRotation);
	}
	else
	{
		CameraArm->TargetArmLength = 5000.0f;
		Camera->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	}
	CameraArm->bUsePawnControlRotation = true;

	Camera->SetupAttachment(CameraArm, USpringArmComponent::SocketName);
}

// Called when the game starts or when spawned
void ABeePlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}
