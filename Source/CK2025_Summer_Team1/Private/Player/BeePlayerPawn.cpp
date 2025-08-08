// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BeePlayerPawn.h"

// Sets default values
ABeePlayerPawn::ABeePlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABeePlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABeePlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABeePlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

