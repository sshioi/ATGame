// Fill out your copyright notice in the Description page of Project Settings.

#include "ATGame.h"
#include "ATCharacterAI.h"

AATCharacterAI::AATCharacterAI(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer.DoNotCreateDefaultSubobject(TEXT("CharacterCameraComp")).DoNotCreateDefaultSubobject(TEXT("CameraCapsuleComp")))
{
	DistanceSquared = 30000.f;
	AttackDistance = 150.f;
	AreaRadius = 200.f;
	FiringDelay = 0.5f;

	AIControllerClass = AATAIController::StaticClass();
}

void AATCharacterAI::PossessedBy(AController* NewController)
{
	AATPlayerState* ATPS = Cast<AATPlayerState>(PlayerState);
	if (ATPS != nullptr)
	{
		ATPS->bIsABot = true;
	}

	Super::PossessedBy(NewController);
}

//void AATCharacterAI::NotifyActorBeginOverlap(AActor* OtherActor)
//{
//	Super::NotifyActorBeginOverlap(OtherActor);
//
//	if (OtherActor->IsA(AATCharacter::StaticClass()) && PlayerState != nullptr && !PlayerState->bIsABot)
//	{
//		UGameplayStatics::ApplyDamage(OtherActor, Damage, NULL, this, UDamageType::StaticClass());
//	}
//}

void AATCharacterAI::FaceRotation(FRotator NewControlRotation, float DeltaTime)
{
	FRotator CurrentRotator = FMath::RInterpTo(GetActorRotation(), NewControlRotation, DeltaTime, 8.f);

	Super::FaceRotation(NewControlRotation, DeltaTime);
}

void AATCharacterAI::Attack(EAttackType EType, int AnimationState)
{
	AttackType = EType;
	if (EType == EAttackType::EAttack_Attack)
	{
		PlayAnimMontage(AttackMontageList[AnimationState]);
	}
	else if (EType == EAttackType::EAttack_Consecutively)
	{
		PlayAnimMontage(AttackMontageList[AnimationState]);
		AttackType = EAttackType::EAttack_Attack;

		if (bIsAttacking)
		{
			FTimerHandle AttackTimerHandle;
			GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &AATCharacterAI::OnAttackEnd, AttackMontageList[AnimationState]->GetPlayLength() + FiringDelay, false);
			AttackType = EAttackType::EAttack_None;
		}
	}
}

void AATCharacterAI::OnAttackEnd()
{
	bIsAttacking = false;
}