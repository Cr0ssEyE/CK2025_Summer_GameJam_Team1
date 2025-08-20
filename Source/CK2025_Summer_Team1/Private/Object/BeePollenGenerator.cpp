// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/BeePollenGenerator.h"

#include "Constant/BeeMaterialParamNames.h"
#include "Game/BeeGameInstance.h"
#include "Game/BeePuzzleManageSubsystem.h"
#include "Object/BeeBuildingMaterialPollen.h"


// Sets default values
ABeePollenGenerator::ABeePollenGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABeePollenGenerator::BeginPlay()
{
	Super::BeginPlay();

	UMaterialInterface* InsideMaterialInterface = MeshComponent->GetMaterial(1);
	if (InsideMaterialInterface)
	{
		InsideMaterialInstance = UMaterialInstanceDynamic::Create(InsideMaterialInterface, this);
		MeshComponent->SetMaterial(1, InsideMaterialInstance);
	}
	
	UBeePuzzleManageSubsystem* PuzzleManageSubsystem = GetGameInstance()->GetSubsystem<UBeePuzzleManageSubsystem>();
	PuzzleManageSubsystem->RegisterPollenGenerator(this);
	SetActorHiddenInGame(true);
}

void ABeePollenGenerator::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);

	if (PollenCount < 1)
	{
		return;
	}
	
	ABeeBuildingMaterialPollen* Pollen = GetWorld()->SpawnActorDeferred<ABeeBuildingMaterialPollen>(PollenObject, FTransform::Identity);
	Pollen->SetBuildingMaterialColor(BuildingMaterialColorEnum, BuildingMaterialColor);
	
	FTransform NewTransform = GetWorld()->GetGameInstanceChecked<UBeeGameInstance>()->GetSubsystem<UBeePuzzleManageSubsystem>()->GetSpawnPoint();
	Pollen->FinishSpawning(NewTransform);
	
	PollenCount--;
	if (PollenCount < 1)
	{
		InsideMaterialInstance->SetScalarParameterValue(PARAM_PUZZLE_OBJECT_VISIBILITY, 0.f);
	}
}
