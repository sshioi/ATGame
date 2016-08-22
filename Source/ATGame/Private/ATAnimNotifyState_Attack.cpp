// Fill out your copyright notice in the Description page of Project Settings.

#include "ATGame.h"
#include "ATAnimNotifyState_Attack.h"

// Begin에서 End 사이에 Tick에 버튼 입력 및 버튼이 눌려진 상태라면 다음 공격이 실행
UATAnimNotifyState_Attack::UATAnimNotifyState_Attack(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

void UATAnimNotifyState_Attack::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	if (MeshComp->GetWorld()->GetNetMode() == NM_DedicatedServer)
	{
		return;
	}

	bIsConsecutively = false;

	Received_NotifyBegin(MeshComp, Animation, TotalDuration);
}

void UATAnimNotifyState_Attack::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	if (MeshComp->GetWorld()->GetNetMode() == NM_DedicatedServer)
	{
		return;
	}

	if (!bIsConsecutively)
	{
		AATCharacter* Pawn = Cast<AATCharacter>(MeshComp->GetOwner());
		if (Pawn && Pawn->AttackType > EAttackType::EAttack_None)
		{
			bIsConsecutively = true;
		}
	}
	Received_NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

void UATAnimNotifyState_Attack::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	if (MeshComp->GetWorld()->GetNetMode() == NM_DedicatedServer)
	{
		return;
	}

	AATCharacter* Pawn = Cast<AATCharacter>(MeshComp->GetOwner());
	if (Pawn && bIsConsecutively && Pawn->AttackType > EAttackType::EAttack_None)
	{
		Pawn->Attack(EAttackType::EAttack_Consecutively, NextAnimation);
	}

	bIsConsecutively = false;
	Received_NotifyEnd(MeshComp, Animation);
}
