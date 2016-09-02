// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimNotifies/AnimNotify.h"
#include "ATAnimNotify_Fire.generated.h"

/**
 * 
 */
UCLASS()
class ATGAME_API UATAnimNotify_Fire : public UAnimNotify
{
	GENERATED_UCLASS_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire")
	FName SocketName;
};
