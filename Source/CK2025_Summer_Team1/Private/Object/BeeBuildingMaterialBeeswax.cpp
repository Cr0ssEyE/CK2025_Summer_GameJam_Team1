// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/BeeBuildingMaterialBeeswax.h"

#include "Constant/BeeCollisionNames.h"
#include "Object/BeeBuildingSlot.h"
#include "Object/Components/BeePuzzlePieceComponent.h"

// Sets default values
ABeeBuildingMaterialBeeswax::ABeeBuildingMaterialBeeswax():
PuzzleMatchingCount(0),
bIsOnPuzzlePlace(0)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABeeBuildingMaterialBeeswax::BeginPlay()
{
	Super::BeginPlay();

	TArray<UActorComponent*> PieceComponents = K2_GetComponentsByClass(UBeePuzzlePieceComponent::StaticClass());
	for (UActorComponent* Component : PieceComponents)
	{
		if (UBeePuzzlePieceComponent* PuzzlePiece = Cast<UBeePuzzlePieceComponent>(Component))
		{
			PuzzlePieces.Add(PuzzlePiece);
		}
	}
}

void ABeeBuildingMaterialBeeswax::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);
	bIsOnPuzzlePlace =false;
	GetWorldTimerManager().SetTimerForNextTick(this, &ABeeBuildingMaterialBeeswax::CheckPuzzlePieceCanSnapToPlace);
}

void ABeeBuildingMaterialBeeswax::NotifyActorOnReleased(FKey ButtonReleased)
{
	Super::NotifyActorOnReleased(ButtonReleased);
	TrySnapPuzzlePieceToPlace();
}

void ABeeBuildingMaterialBeeswax::CheckPuzzlePieceCanSnapToPlace()
{
	if (!bIsSelected && !bIsOnPuzzlePlace)
	{
		TrySnapPuzzlePieceToPlace();
		return;
	}

	PuzzleMatchingCount = 0;
	FHitResult HitResult;
	
	for (const UBeePuzzlePieceComponent* PuzzlePiece : PuzzlePieces)
	{
		FVector Start = PuzzlePiece->GetComponentLocation();
		FVector End = Start - FVector(0.f, 0.f, 1000.f);

		bool bHit = GetWorld()->LineTraceSingleByChannel(
			HitResult,
			Start,
			End,
			ECC_TRACE_PUZZLE_SLOT_OBJECT
		);
		DrawDebugLine(GetWorld(), Start, End, bHit ? FColor::Green : FColor::Red, false, 0.1f, 0, 1.0f);
		if (bHit)
		{
			PuzzleMatchingCount++;
		}
	}
	
	GetWorldTimerManager().SetTimerForNextTick(this, &ABeeBuildingMaterialBeeswax::CheckPuzzlePieceCanSnapToPlace);
}

void ABeeBuildingMaterialBeeswax::TrySnapPuzzlePieceToPlace()
{
	if (PuzzlePieces.Num() == 0 || PuzzleMatchingCount == 0)
	{
		return;
	}
	
	const int32 CurrentPuzzleMatchingCount = PuzzleMatchingCount;
	FHitResult HitResult;

	UBeePuzzlePieceComponent* TestPuzzlePiece = PuzzlePieces[0];
	
	const FVector Start = TestPuzzlePiece->GetComponentLocation();
	const FVector End = Start - FVector(0.f, 0.f, 1000.f);

	const bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECC_TRACE_PUZZLE_SLOT_OBJECT
	);
	
	if (!bHit || CurrentPuzzleMatchingCount < PuzzlePieces.Num())
	{
		bIsOnPuzzlePlace = false;
		PuzzleMatchingCount = 0;
		SetActorLocation(LastPlacedPoint);
		return;
	}
	
	ABeeBuildingSlot* BuildingSlot = Cast<ABeeBuildingSlot>(HitResult.GetActor());
	if (!BuildingSlot)
	{
		ensure(false);
		return;
	}
	
	const USceneComponent* TestSlotComponent = BuildingSlot->GetPuzzleSlotComponent();
	//TODO: 위치 조정 개선 필요
	const FVector Distance = TestSlotComponent->GetComponentLocation() - TestPuzzlePiece->GetComponentLocation();
	SetActorLocation(GetActorLocation() + Distance);
	SetLastPlacedPoint();
	bIsOnPuzzlePlace = true;
}

