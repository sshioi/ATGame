// Fill out your copyright notice in the Description page of Project Settings.

#include "ATGame.h"
#include "ATWeapon_Shield.h"

AATWeapon_Shield::AATWeapon_Shield(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer.DoNotCreateDefaultSubobject("WeaponRMeshComp"))
{
	WeaponMeshComponent = ObjectInitializer.CreateOptionalDefaultSubobject<UStaticMeshComponent>(this, TEXT("WeaponLMeshComp"));
	if (WeaponMeshComponent != nullptr)
	{
		WeaponMeshComponent->SetupAttachment(RootComponent);
		WeaponMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		WeaponMeshComponent->SetCastShadow(false);
	}

	HandsAttachSocketName = TEXT("Weapon_L");
}