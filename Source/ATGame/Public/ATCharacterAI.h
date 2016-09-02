// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ATCharacter.h"
#include "ATCharacterAI.generated.h"

/**
 * 
 */
UCLASS()
class ATGAME_API AATCharacterAI : public AATCharacter
{
	GENERATED_UCLASS_BODY()

public:
	virtual void PossessedBy(AController* NewController) override;
	//virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void FaceRotation(FRotator NewControlRotation, float DeltaTime = 0.f ) override;

	virtual void Attack(EAttackType EType, int AnimationState = 0) override;
	virtual void OnAttackEnd();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float DistanceSquared;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float AttackDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float AreaRadius;
};
