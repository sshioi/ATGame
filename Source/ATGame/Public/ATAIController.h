// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "ATAIController.generated.h"

/**

 */
UCLASS()
class ATGAME_API AATAIController : public AAIController
{
	GENERATED_UCLASS_BODY()

public:
	virtual void Possess(APawn* Pawn) override;
	virtual void UpdateControlRotation(float DeltaTime, bool bUpdatePawn = true) override;

	virtual void Attack();
	void SetTargetEnemy(AATCharacter* PawnTarget);
	class AATCharacter* GetEnemy();

	UFUNCTION(BlueprintCallable, Category = "AI")
	void FindClosestEnemy();
	
public:
	UPROPERTY()
	class AATPlayerState* ATPlayerState;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName TargetEnemyKeyName;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName AITypeKeyName;

private:
	//Behavior Tree component reference
	UPROPERTY(Transient)
	class UBehaviorTreeComponent* BehaviorComponent;

	//Blackboard comp ref
	UPROPERTY(Transient)
	class UBlackboardComponent* BlackboardComponent;
};
