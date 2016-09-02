// Fill out your copyright notice in the Description page of Project Settings.

#include "ATGame.h"
#include "ATGameGameMode.h"

AATGameGameMode::AATGameGameMode(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

// Parse options for this game...
void AATGameGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	for (TActorIterator<AATSpawnManager> It(GetWorld()); It; ++It)
	{
		// 무조건 한개만 존재
		SpawnManager = *It;
		break;
	}
}

void AATGameGameMode::GenericPlayerInitialization(AController* C)
{
	AATPlayerController* PC = Cast<AATPlayerController>(C);
	if (PC != NULL)
	{
		// Notify the game that we can now be muted and mute others
		UpdateGameplayMuteList(PC);
		
		PC->ClientSetHUD(HUDClass);

		ReplicateStreamingStatus(PC);
	}
}