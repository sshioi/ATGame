// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ATAIController.h"
#include "ATAIController_Magic.generated.h"

/**
 * 
 */
UCLASS()
class ATGAME_API AATAIController_Magic : public AATAIController
{
	GENERATED_UCLASS_BODY()

public:
	virtual void Attack() override;
};
