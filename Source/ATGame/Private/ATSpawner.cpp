// Fill out your copyright notice in the Description page of Project Settings.

#include "ATGame.h"
#include "ATSpawner.h"


// Sets default values
AATSpawner::AATSpawner(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
#if WITH_EDITORONLY_DATA
	SpawnerArrow = ObjectInitializer.CreateDefaultSubobject<UArrowComponent>(this, TEXT("SpawnerArrow"));
#endif
}

AATCharacter* AATSpawner::Spawn(UClass* SpawnClass)
{
	return GetWorld()->SpawnActor<AATCharacter>(SpawnClass, GetActorLocation(), GetActorRotation());
}