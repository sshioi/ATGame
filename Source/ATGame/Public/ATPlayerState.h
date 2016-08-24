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

	// 로비 연동시 가져올 아이템 설정
	virtual void ApplyItem();
};
