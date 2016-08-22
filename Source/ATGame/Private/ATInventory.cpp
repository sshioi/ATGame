// Fill out your copyright notice in the Description page of Project Settings.

#include "ATGame.h"
#include "ATInventory.h"


// Sets default values
AATInventory::AATInventory(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	RootComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent, USceneComponent>(this, TEXT("DummyRoot"), false);

	PrimaryActorTick.bCanEverTick = true;
}

void AATInventory::GivenTo(AATCharacter* NewOwner, bool bAutoActivate)
{
	Instigator = NewOwner;
	ATOwner = NewOwner;
	SetOwner(NewOwner);
	PrimaryActorTick.AddPrerequisite(Instigator, Instigator->PrimaryActorTick);
	//ClientGivenTo(Instigator, bAutoActivate);
}

void AATInventory::ClientGivenTo_Implementation(APawn* NewInstigator, bool bAutoActivate)
{
	if (NewInstigator != nullptr)
	{
		Instigator = NewInstigator;
	}
}