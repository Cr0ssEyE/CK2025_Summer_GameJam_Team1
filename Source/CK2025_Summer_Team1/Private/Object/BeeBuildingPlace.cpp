// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/BeeBuildingPlace.h"
#include "Constant/BeeCollisionNames.h"


// Sets default values
ABeeBuildingPlace::ABeeBuildingPlace()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionProfileName(CP_PLACE_OBJECT);
	
	PuzzleSlotComponent = CreateDefaultSubobject<UBeePuzzleSlotComponent>(TEXT("PuzzleSlotComponent"));
	PuzzleSlotComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABeeBuildingPlace::BeginPlay()
{
	Super::BeginPlay();
	
}

