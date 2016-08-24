// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTService.h"
#include "ATBTService_AttackEnemy.generated.h"

/**
 * 
 */
UCLASS()
class ATGAME_API UATBTService_AttackEnemy : public UBTService
{
	GENERATED_UCLASS_BODY()

public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void SetOwner(AActor* ActorOwner) override;

protected:
	AATAIController* AIController;
};
