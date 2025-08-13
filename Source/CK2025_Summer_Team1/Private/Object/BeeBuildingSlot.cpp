// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/BeeBuildingSlot.h"
#include "Constant/BeeCollisionNames.h"
#include "Game/BeePuzzleManageSubsystem.h"


// Sets default values
ABeeBuildingSlot::ABeeBuildingSlot()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionProfileName(CP_PLACE_OBJECT);
	
	PuzzleCenterComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("PuzzleCenterComponent"));
	PuzzleCenterComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABeeBuildingSlot::BeginPlay()
{
	Super::BeginPlay();

	GetGameInstance()->GetSubsystem<UBeePuzzleManageSubsystem>()->RegisterPuzzleSlot(this);
}

