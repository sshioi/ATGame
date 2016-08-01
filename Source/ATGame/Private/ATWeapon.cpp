// Fill out your copyright notice in the Description page of Project Settings.

#include "ATGame.h"
#include "ATWeapon.h"

AATWeapon::AATWeapon(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	WeaponMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("WeaponMesh"));
	if (WeaponMesh != nullptr)
	{
		WeaponMesh->SetOnlyOwnerSee(false);
		WeaponMesh->SetOwnerNoSee(false);

		WeaponMesh->SetupAttachment(RootComponent);
		WeaponMesh->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
	}
	
	WeaponMeshComponent = ObjectInitializer.CreateOptionalDefaultSubobject<UStaticMeshComponent>(this, TEXT("WeaponMeshComp"));
	if (WeaponMeshComponent != nullptr)
	{
		//WeaponMeshComponent->SetupAttachment(GetMesh(), TEXT("Weapon"));
		WeaponMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		WeaponMeshComponent->SetCastShadow(false);
	}

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	HandsAttachSocketName = TEXT("Weapon_R");
}

void AATWeapon::AttachToOwner_Implementation()
{
	if (ATOwner == NULL)
	{
		return;
	}

	if (WeaponMesh != NULL && WeaponMesh->SkeletalMesh != NULL)
	{
		WeaponMesh->AttachToComponent(ATOwner->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, HandsAttachSocketName);
	}

	Super::RegisterAllComponents();
	//RegisterAllActorTickFunctions(true, true);

	//ATOwner->weapon = this;
}
