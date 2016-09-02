// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ATCharacterAI.h"
#include "ATCharacterAI_Magic.generated.h"

/**
 * 
 */
UCLASS()
class ATGAME_API AATCharacterAI_Magic : public AATCharacterAI
{
	GENERATED_UCLASS_BODY()

public:
	virtual void Attack(EAttackType EType, int AnimationState = 0) override;
	virtual void OnAttackEnd() override;
};
