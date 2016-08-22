// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ATInventory.generated.h"

UCLASS(Blueprintable, Abstract, notplaceable)
class ATGAME_API AATInventory : public AActor
{
	GENERATED_UCLASS_BODY()
	
public:
	AATCharacter* GetATOwner() const
	{
		checkSlow(ATOwner == GetATOwner());
		return ATOwner;
	}

	virtual void GivenTo(AATCharacter* NewOwner, bool bAutoActivate);

protected:
	UFUNCTION(Client, Reliable)
	void ClientGivenTo(APawn* NewInstigator, bool bAutoActivate);

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Inventory")
	AATCharacter* ATOwner;

};
