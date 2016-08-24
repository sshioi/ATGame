// Fill out your copyright notice in the Description page of Project Settings.

#include "ATGame.h"
#include "ATAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"

AATAIController::AATAIController(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	BehaviorComponent = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComponent"));
	BlackboardComponent = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComponent"));

	TargetEnemyKeyName = "TargetEnemy";
}

void AATAIController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);

	AATCharacterAI* ATBot = Cast<AATCharacterAI>(Pawn);

	//Initialize blackboard
	if (ATBot && ATBot->BehaviorTree && ATBot->BehaviorTree->BlackboardAsset)
	{
		BlackboardComponent->InitializeBlackboard(*ATBot->BehaviorTree->BlackboardAsset);
	}

	BehaviorComponent->StartTree(*ATBot->BehaviorTree);
}

void AATAIController::UpdateControlRotation(float DeltaTime, bool bUpdatePawn)
{
	if (!GetFocalPoint().IsZero() && GetPawn())
	{
		FVector Direction = GetFocalPoint() - GetPawn()->GetActorLocation();
		FRotator NewContorolRotation = Direction.Rotation();

		NewContorolRotation.Yaw = FRotator::ClampAxis(NewContorolRotation.Yaw);
		SetControlRotation(NewContorolRotation);

		if (GetPawn() && bUpdatePawn)
		{
			GetPawn()->FaceRotation(NewContorolRotation, DeltaTime);
		}
	}
}

void AATAIController::FindClosestEnemy()
{
	AATCharacterAI* MyBot = Cast<AATCharacterAI>(GetPawn());

	if (MyBot != nullptr)
	{
		float ClosestEnemyDistSq = MyBot->DistanceSquared;
		AATCharacter* ClosestEnemy = NULL;

		TArray<AActor*> ActorsArray;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AATCharacter::StaticClass(), ActorsArray);

		for (auto Character = ActorsArray.CreateIterator(); Character; ++Character)
		{
			AATCharacter* ATEnemy = Cast<AATCharacter>(*Character);
			if (ATEnemy != nullptr && ATEnemy->PlayerState != nullptr && !ATEnemy->PlayerState->bIsABot)
			{
				// 가장 가까운 적을 찾는다.
				const float DistSq = (ATEnemy->GetActorLocation() - MyBot->GetActorLocation()).SizeSquared();
				if (DistSq < ClosestEnemyDistSq)
				{
					ClosestEnemyDistSq = DistSq;
					ClosestEnemy = ATEnemy;
				}
			}
		}

		if (ClosestEnemy != nullptr)
		{
			SetTargetEnemy(ClosestEnemy);
		}
	}
}

void AATAIController::Attack()
{
	AATCharacter* Enemy = GetEnemy();
	AATCharacterAI* MyBot = Cast<AATCharacterAI>(GetPawn());
	if (Enemy != nullptr && MyBot != nullptr)
	{
		const float Dist = (Enemy->GetActorLocation() - MyBot->GetActorLocation()).Size2D();
		if (Dist < MyBot->AttackDistance)
		{
			MyBot->Attack(EAttackType::EAttack_Attack);
		}
		else
		{
			MyBot->Attack(EAttackType::EAttack_None);
		}
	}
}

void AATAIController::SetTargetEnemy(AATCharacter* PawnTarget)
{
	if (BlackboardComponent)
	{
		BlackboardComponent->SetValueAsObject(TargetEnemyKeyName, PawnTarget);
		SetFocus(PawnTarget);
	}
}

AATCharacter* AATAIController::GetEnemy()
{
	if (BlackboardComponent)
	{
		return Cast<AATCharacter>(BlackboardComponent->GetValueAsObject(TargetEnemyKeyName));
	}
	return NULL;
}