// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/BeeSelectableActorBase.h"


// Sets default values
ABeeSelectableActorBase::ABeeSelectableActorBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	OutlineMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OutlineComponent"));
	OutlineMeshComponent->SetupAttachment(RootComponent);

	bIsSelected = false;
	bIsHovered = false;
}

// Called when the game starts or when spawned
void ABeeSelectableActorBase::BeginPlay()
{
	Super::BeginPlay();
	UMaterialInterface* OutlineMaterialInterface = OutlineMeshComponent->GetMaterial(0);
	if (OutlineMaterialInterface)
	{
		OutlineMaterialInstance = UMaterialInstanceDynamic::Create(OutlineMaterialInterface, this);
		OutlineMeshComponent->SetMaterial(0, OutlineMaterialInstance);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Outline material not found on %s"), *GetName());
	}
}

// Called every frame
void ABeeSelectableActorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABeeSelectableActorBase::NotifyActorBeginCursorOver()
{
	Super::NotifyActorBeginCursorOver();
	bIsHovered = true;
	OutlineMaterialInstance->SetScalarParameterValue(TEXT("OutlineIntensity"), 1.f);
}

void ABeeSelectableActorBase::NotifyActorEndCursorOver()
{
	Super::NotifyActorEndCursorOver();
	bIsHovered = false;
	OutlineMaterialInstance->SetScalarParameterValue(TEXT("OutlineIntensity"), 0.f);
}
