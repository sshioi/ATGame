// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "ATPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class ATGAME_API AATPlayerState : public APlayerState
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION()
	class AATCharacter* GetATCharacter();

	// �κ� ������ ������ ������ ����
	virtual void ApplyItem();
};
