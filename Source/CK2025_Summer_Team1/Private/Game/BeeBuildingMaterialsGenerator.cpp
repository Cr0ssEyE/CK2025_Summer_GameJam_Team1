// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/BeeBuildingMaterialsGenerator.h"

#include "Data/BeeStageInfoDataAsset.h"
#include "Game/BeePuzzleManageSubsystem.h"
#include "Object/Components/BeePuzzlePieceSpawnPoint.h"


// Sets default values
ABeeBuildingMaterialsGenerator::ABeeBuildingMaterialsGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABeeBuildingMaterialsGenerator::BeginPlay()
{
	Super::BeginPlay();

	GetGameInstance()->GetSubsystem<UBeePuzzleManageSubsystem>()->OnFadeStateChanged.AddDynamic(this, &ABeeBuildingMaterialsGenerator::OnFadeStateChanged);

	TArray<UActorComponent*> PieceComponents = K2_GetComponentsByClass(UBeePuzzlePieceSpawnPoint::StaticClass());
	for (UActorComponent* Component : PieceComponents)
	{
		if (UBeePuzzlePieceSpawnPoint* PuzzlePiece = Cast<UBeePuzzlePieceSpawnPoint>(Component))
		{
			PuzzlePieceSpawnPoints.Add(PuzzlePiece);
		}
	}

	if (PuzzlePieceSpawnPoints.Num() <= 0)
	{
		ensureMsgf(false, TEXT("Puzzle piece spawn point not found"));
	}
}

void ABeeBuildingMaterialsGenerator::OnFadeStateChanged(bool bIsFadingIn)
{
	if (!bIsFadingIn)
	{
		return;
	}
	
	for (auto PuzzlePieceData : StageInfoDataAsset->PuzzlePieceDataArray)
	{
		for (int32 i = 0; i < PuzzlePieceData.PuzzlePieceCount; ++i)
		{
			if (PuzzlePieceSpawnPoints.IsValidIndex(i))
			{
				UBeePuzzlePieceSpawnPoint* SpawnPoint = PuzzlePieceSpawnPoints[FMath::RandRange(0, PuzzlePieceSpawnPoints.Num())];
				if (SpawnPoint)
				{
					GetWorld()->SpawnActor<AActor>(PuzzlePieceData.PuzzlePieceBlueprint, SpawnPoint->GetComponentLocation(), FRotator::ZeroRotator);
					PuzzlePieceSpawnPoints.Remove(SpawnPoint);
				}
				else
				{
					i--;
				}
			}
		}
	}
}
