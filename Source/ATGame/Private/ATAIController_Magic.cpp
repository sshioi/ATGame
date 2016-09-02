// Fill out your copyright notice in the Description page of Project Settings.

#include "ATGame.h"
#include "ATAIController_Magic.h"

AATAIController_Magic::AATAIController_Magic(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

void AATAIController_Magic::Attack()
{
	AATCharacter* Enemy = GetEnemy();
	AATCharacterAI* MyBot = Cast<AATCharacterAI>(GetPawn());
	if (Enemy != nullptr && MyBot != nullptr && !MyBot->bIsAttacking)
	{
		const float Dist = (Enemy->GetActorLocation() - MyBot->GetActorLocation()).Size2D();
		if (Dist < MyBot->AttackDistance)
		{
			MyBot->bIsAttacking = true;
			MyBot->Attack(EAttackType::EAttack_Attack);
		}
	}
}
