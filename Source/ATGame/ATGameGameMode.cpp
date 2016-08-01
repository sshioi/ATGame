// Fill out your copyright notice in the Description page of Project Settings.

#include "ATGame.h"
#include "ATGameGameMode.h"

AATGameGameMode::AATGameGameMode(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
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