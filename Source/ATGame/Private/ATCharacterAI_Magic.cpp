// Fill out your copyright notice in the Description page of Project Settings.

#include "ATGame.h"
#include "ATCharacterAI_Magic.h"

AATCharacterAI_Magic::AATCharacterAI_Magic(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer.DoNotCreateDefaultSubobject(TEXT("AttackCollisionSphere")))
{
	AIControllerClass = AATCharacterAI_Magic::StaticClass();
}

void AATCharacterAI_Magic::Attack(EAttackType EType, int AnimationState)
{
	if (AttackMontageList[AnimationState] != nullptr && EType == EAttackType::EAttack_Attack && !ATAnimInstance->Montage_IsPlaying(AttackMontageList[AnimationState]))
	{
		PlayAnimMontage(AttackMontageList[AnimationState]);

		if (bIsAttacking)
		{
			FTimerHandle AttackTimerHandle;
			GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &AATCharacterAI_Magic::OnAttackEnd, AttackMontageList[AnimationState]->GetPlayLength() + FiringDelay, false);
			AttackType = EAttackType::EAttack_None;
			GetCharacterMovement()->MaxWalkSpeed = 0.f;
		}
	}
}

void AATCharacterAI_Magic::OnAttackEnd()
{
	bIsAttacking = false;
	GetCharacterMovement()->MaxWalkSpeed = OrgMaxWalkSpeed;
}