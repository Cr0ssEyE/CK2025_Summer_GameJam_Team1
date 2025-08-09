// Fill out your copyright notice in the Description page of Project Settings.


#include "Object/BeePickUpObjectBase.h"

#include "Constant/BeeCollisionNames.h"

ABeePickUpObjectBase::ABeePickUpObjectBase()
{
	MeshComponent->SetCollisionProfileName(CP_PUZZLE_OBJECT);
}

void ABeePickUpObjectBase::BeginPlay()
{
	Super::BeginPlay();
}

void ABeePickUpObjectBase::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);
}

void ABeePickUpObjectBase::NotifyActorOnReleased(FKey ButtonReleased)
{
	Super::NotifyActorOnReleased(ButtonReleased);
}
