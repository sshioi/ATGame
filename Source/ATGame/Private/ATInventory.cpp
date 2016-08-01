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