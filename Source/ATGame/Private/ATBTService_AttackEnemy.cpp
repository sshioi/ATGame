// Fill out your copyright notice in the Description page of Project Settings.

#include "ATGame.h"
#include "ATBTService_AttackEnemy.h"

UATBTService_AttackEnemy::UATBTService_AttackEnemy(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	NodeName = "Run Attack Enemy";

	// all blueprint based nodes must create instances
	bCreateNodeInstance = true;
}

void UATBTService_AttackEnemy::SetOwner(AActor* InActorOwner)
{
	AIController = Cast<AATAIController>(InActorOwner);
}

void UATBTService_AttackEnemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (AIController != nullptr)
	{
		AIController->Attack();
	}
}


