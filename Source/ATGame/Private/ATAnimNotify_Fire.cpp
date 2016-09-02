// Fill out your copyright notice in the Description page of Project Settings.

#include "ATGame.h"
#include "ATAnimNotify_Fire.h"

UATAnimNotify_Fire::UATAnimNotify_Fire(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void UATAnimNotify_Fire::Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation)
{
	AATCharacter* Pawn = Cast<AATCharacter>(MeshComp->GetOwner());
	if (Pawn != nullptr)
	{
		Pawn->StartFire(SocketName);
	}
}
