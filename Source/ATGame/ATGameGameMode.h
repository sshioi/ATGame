// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "ATGameGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ATGAME_API AATGameGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()

public:
	virtual void GenericPlayerInitialization(AController* C) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TArray<TSubclassOf<class AATInventory>> GameModeInventory;
};
