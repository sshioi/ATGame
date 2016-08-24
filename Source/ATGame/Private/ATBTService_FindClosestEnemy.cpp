// Fill out your copyright notice in the Description page of Project Settings.

#include "ATGame.h"
#include "ATBTService_FindClosestEnemy.h"

UATBTService_FindClosestEnemy::UATBTService_FindClosestEnemy(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	NodeName = "Run Find Closest Enemy";

	// all blueprint based nodes must create instances
	bCreateNodeInstance = true;
}

void UATBTService_FindClosestEnemy::SetOwner(AActor* InActorOwner)
{
	AIController = Cast<AATAIController>(InActorOwner);
}

void UATBTService_FindClosestEnemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (AIController != nullptr)
	{
		AIController->FindClosestEnemy();
	}
}