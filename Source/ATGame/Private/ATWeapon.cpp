// Fill out your copyright notice in the Description page of Project Settings.

#include "ATGame.h"
#include "ATWeapon.h"

AATWeapon::AATWeapon(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	WeaponMeshComponent = ObjectInitializer.CreateOptionalDefaultSubobject<UStaticMeshComponent>(this, TEXT("WeaponRMeshComp"));
	if (WeaponMeshComponent != nullptr)
	{
		WeaponMeshComponent->SetupAttachment(RootComponent);
		WeaponMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		WeaponMeshComponent->SetCastShadow(false);
	}

	HandsAttachSocketName = TEXT("Weapon_R");
}

void AATWeapon::GivenTo(AATCharacter* NewOwner, bool bAutoActivate)
{
	Super::GivenTo(NewOwner, bAutoActivate);
	AttachToOwner();
}

void AATWeapon::AttachToOwner()
{
	if (ATOwner == NULL)
	{
		return;
	}

	if (WeaponMeshComponent != nullptr)
	{
		WeaponMeshComponent->AttachToComponent(ATOwner->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, HandsAttachSocketName);
	}
	Super::RegisterAllComponents();
	RegisterAllActorTickFunctions(true, true);
	//ATOwner->weapon = this;
}

void AATWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

#if WITH_EDITOR
	if (MeleeCollision != nullptr && bIsDrawWeaponCollision)
	{
		DrawDebugCapsule(GetWorld(), MeleeCollision->GetComponentLocation(), MeleeCollision->GetScaledCapsuleHalfHeight(), MeleeCollision->GetScaledCapsuleRadius(), MeleeCollision->GetComponentQuat(), FColor::Green);
	}
#endif	// WITH_EDITOR
}
