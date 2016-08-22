// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "ATAnimNotifyState_Attack.generated.h"

/**
 * 
 */
UCLASS()
class ATGAME_API UATAnimNotifyState_Attack : public UAnimNotifyState
{
	GENERATED_UCLASS_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime) override;
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	int NextAnimation;

	bool bIsConsecutively;
};
