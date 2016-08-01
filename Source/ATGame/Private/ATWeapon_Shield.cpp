// Fill out your copyright notice in the Description page of Project Settings.

#include "ATGame.h"
#include "ATWeapon_Shield.h"

AATWeapon_Shield::AATWeapon_Shield(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer.DoNotCreateDefaultSubobject(TEXT("WeaponMeshComp")))
{
	ShieldMeshComponent = ObjectInitializer.CreateOptionalDefaultSubobject<UStaticMeshComponent>(this, TEXT("ShieldMeshComp"));
	if (ShieldMeshComponent != nullptr)
	{
		//ShieldMeshComponent->SetupAttachment(GetMesh(), TEXT("Shield"));
		ShieldMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		ShieldMeshComponent->SetCastShadow(false);
	}
}


