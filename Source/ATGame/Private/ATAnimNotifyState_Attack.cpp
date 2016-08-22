// Fill out your copyright notice in the Description page of Project Settings.

#include "ATGame.h"
#include "ATAnimNotifyState_Attack.h"

// Begin���� End ���̿� Tick�� ��ư �Է� �� ��ư�� ������ ���¶�� ���� ������ ����
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
