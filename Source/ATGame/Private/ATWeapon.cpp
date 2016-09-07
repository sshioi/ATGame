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

	Damage = 10.f;
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

	FWeaponInfo WeaponInfo;
	WeaponInfo.ATWeapon = this;
	WeaponInfo.SocketName = HandsAttachSocketName;

	ATOwner->ATWeaponList.Add(WeaponInfo);
}

void AATWeapon::DetachFromOwner()
{
	bIsDrawWeaponCollision = false;
	// unregister components so they go away
	UnregisterAllComponents();
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

void AATWeapon::FireShot()
{
	ATOwner->bIsAttacking = true;
	if (ProjectileClass != nullptr)
	{
		FireProjectile(ProjectileClass)->Damage = Damage;
	}
}

AATProjectile* AATWeapon::FireProjectile(const TSubclassOf<AATProjectile>& ProjectileClass)
{
	checkSlow(ProjectileClass != nullptr);

	FVector SpawnLocation = ATOwner->GetActorLocation() + ATOwner->GetActorRotation().RotateVector(FVector(100.f, 30.f, 10.f));

	if (GetWorld() != NULL)
	{
		return GetWorld()->SpawnActor<AATProjectile>(ProjectileClass, ATOwner->GetActorLocation(), ATOwner->GetActorRotation());
	}
	return NULL;
}

void AATWeapon::OnOverlapBegin(class UPrimitiveComponent* HitComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		AATCharacter* Charater = Cast<AATCharacter>(OtherActor);
		if (Charater != nullptr && Charater->CurrentWeapon != this && this->ATOwner->bIsAttacking && this->ATOwner->bIsBot() != Charater->bIsBot())
		{
			UGameplayStatics::ApplyPointDamage(SweepResult.Actor.Get(), Damage, -SweepResult.ImpactNormal, SweepResult, NULL, this, UDamageType::StaticClass());
			this->ATOwner->bIsAttacking = false;
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, TEXT("Projectile Collision"));
		}
	}
}